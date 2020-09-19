/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 07:35:49 by matrus            #+#    #+#             */
/*   Updated: 2020/09/17 07:35:53 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "exec_all_commands.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

typedef struct	s_exec_info
{
	int		fd_prev;
	int		fd_out;
	int		fd_pipe[2];
	pid_t	pid;
	int		status;
}				t_exec_info;

static int		parse_stop_status(int stat)
{
	int	sig;

	if (WIFSIGNALED(stat))
	{
		sig = WTERMSIG(stat);
		if (sig == SIGQUIT)
		{
			ft_putstr_fd("\nQuit:\t", 2);
			ft_putnbr_fd(SIGQUIT, 2);
			ft_putchar_fd('\n', 2);
		}
		return WTERMSIG(stat);
	}
	return (WEXITSTATUS(stat));
}

void			wait_child(t_exec_info *inf, int *status)
{
	int		wpid;

	while (1)
	{
		wpid = waitpid(inf->pid, status, WUNTRACED);		// TODO: errno might be set
		if (wpid >= 0)
			break;
		if (g_sigint)
			kill(inf->pid, SIGINT);
	}
	g_sigint = 0;
}

static int		exec_extern(t_exec_info *inf, t_command *cmd, t_env *env)
{
	int	status;

	inf->pid = fork();
	if (inf->pid == 0)
	{
		// Child here
		signal(SIGQUIT, SIG_DFL);
		// Make redirects in here. If redirect, pipeline is ignored.
		dup2(inf->fd_prev, 0);
		// Make redirects out here. If redirect, pipeline is ignored.
		dup2(inf->fd_out, 1);
		// Exec smth
		status = execve(cmd->cmd_name, cmd->args, env->transfer_control(env));
		// If Error -> write smth;
		ft_putendl_fd("Oops! Bad execution:(", 2);	// TODO: err 'zsh: quit       ./minishell'
		exit(status);
	}
	else if (inf->pid < 0)
	{
		// Fork error here
		ft_putendl_fd("Forking error", 1); // TODO: error fd 2
		return (-1);
	}
	else
	{
		// Parent here
		wait_child(inf, &status);
//		waitpid(inf->pid, &status, WUNTRACED);
	}
	return (parse_stop_status(status));
}


/*static int		open_out_redirect_if_exist(const char *filename, int is_double)
{
	int	fd;
	int	flags;

	if (!filename)
		return (1);
	flags = O_WRONLY | (is_double ? O_APPEND : O_TRUNC);
	fd = open(filename, flags); //TODO: error?
	return (fd < 0 ? 1 : fd);
}*/

static int		safe_open_out_redirect(t_exec_info *exe_i, t_command *cmd)
{
	int	fd;
	int	flags;

	if (exe_i->fd_out != 1)
		close(exe_i->fd_out);
	flags = O_WRONLY | (cmd->last_is_double ? O_APPEND : O_TRUNC);
	fd = open(cmd->redir_out_last, flags);
	return (fd < 0 ? 1 : fd);
}

/*static int		open_in_redirect_if_exist(char **redirects_tab)
{
	char	*filename;
	int		fd;

	filename = NULL;
	while (*redirects_tab)
		filename = *redirects_tab++;
	fd = open(filename, O_RDONLY); //TODO: error?
	return (fd < 0 ? 0 : fd);
}*/

static int		safe_open_in_redirect(t_exec_info *exe_i, t_command *cmd)
{
	char	**filenames_tab;
	char	*filename;
	int		fd;

	filenames_tab = cmd->redir_in;
	filename = NULL;
	while (*filenames_tab)
		filename = *filenames_tab++;
	if (filename)
	{
		if (exe_i->fd_prev != 0)
			close(exe_i->fd_prev);
		fd = open(filename, O_RDONLY); //TODO: error?
		return (fd < 0 ? 0 : fd);
	}
	return (exe_i->fd_prev);
}

/*
**	function tries to create a pipe
**	then select which command to exec (builtin / extern)
**	executed functions write their output into a PIPE
**	PIPE.OUT saved till next execute, next execute will read from that fd
**	if separator is not a pipeline then outputs goes to redirections or to fd=1
*/
int				execute_command(t_func_ptr builtin, t_command *cmd, t_env *env)
{
	static t_exec_info	exe_i;
	int					is_pipe;

	is_pipe = cmd->next_operator[0] == '|' && cmd->next_operator[1] == '\0';
	if (is_pipe)
	{
		if (pipe(exe_i.fd_pipe) < 0)
			ft_putendl_fd("pipe error", 1); // TODO: error managment ERRNO
	}
	exe_i.fd_out = (is_pipe) ? exe_i.fd_pipe[1] : 1;
	if (cmd->redir_out_last)
		exe_i.fd_out = safe_open_out_redirect(&exe_i, cmd);
	if (cmd->redir_in)
		exe_i.fd_prev = safe_open_in_redirect(&exe_i, cmd);
	if (builtin)
		exe_i.status = builtin(cmd->args, exe_i.fd_prev, exe_i.fd_out, env);
	else
		exe_i.status = exec_extern(&exe_i, cmd, env);
	if (exe_i.fd_prev != 0)
		close(exe_i.fd_prev);
	if (is_pipe && !cmd->redir_out_last)
		close(exe_i.fd_pipe[1]);
	exe_i.fd_prev = (is_pipe) ? exe_i.fd_pipe[0] : 0;
	return (exe_i.status);
}

/*
int				execute_command(t_func_ptr builtin, t_command *cmd, t_env *env)
{
	static t_exec_info	exe_i;
	int					is_pipe;

	is_pipe = cmd->next_operator[0] == '|' && cmd->next_operator[1] == '\0';
	if (cmd->redir_out_last)
		is_pipe = 0;
	if (cmd->redir_in)
		close_and_set_ft_prev(&exe_i.fd_prev, cmd->redir_in);
	exe_i.fd_pipe[0] = 0;
	exe_i.fd_pipe[1] = open_out_redirect_if_exist(cmd->redir_out_last, cmd->last_is_double);
	if (is_pipe)
		if ((pipe(exe_i.fd_pipe)) < 0)
			ft_putendl_fd("pipe error", 1);

	if (builtin)
		exe_i.status = builtin(cmd->args, exe_i.fd_prev, exe_i.fd_pipe[1], env);
	else
		exe_i.status = exec_extern(&exe_i, cmd, env);

	if (exe_i.fd_prev > 0)
		close(exe_i.fd_prev);

	if (is_pipe || exe_i.fd_pipe[1] != 1)
		close(exe_i.fd_pipe[1]);

	if (!is_pipe && cmd->next_operator[0] == '|' && cmd->next_operator[1] == '\0')
		exe_i.fd_prev = exe_i.fd_pipe[0];

	return (exe_i.status);
}
*/
