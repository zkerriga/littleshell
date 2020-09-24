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

#include "exec_all_commands.h"
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include "error_manager.h"
#include "builtin_functions.h"

void			wait_child(t_exec_info *inf, int *status)
{
	int		wpid;

	while (1)
	{
		errno = 0;
		wpid = waitpid(inf->pid, status, WUNTRACED);
		if (errno)
			errman(errno, NULL);
		if (wpid >= 0)
			break ;
		if (g_sigint)
			kill(inf->pid, SIGINT);
	}
}

static int		exec_extern(t_exec_info *inf, t_command *cmd, t_env *env)
{
	int	status;

	inf->pid = fork();
	if (inf->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		dup2(inf->fd_prev, 0);
		dup2(inf->fd_out, 1);
		status = execve(cmd->cmd_name, cmd->args, env->transfer_control(env));
		write_err(cmd->cmd_name, NULL, "bad execution");
		exit(status);
	}
	else if (inf->pid < 0)
	{
		errman(NOEXIT, "forking error");
		return (-1);
	}
	else
	{
		wait_child(inf, &status);
	}
	return (parse_stop_status(status));
}

static int		safe_open_out_redirect(t_exec_info *exe_i, t_command *cmd)
{
	int	fd;
	int	flags;

	if (exe_i->fd_out != 1)
		close(exe_i->fd_out);
	flags = O_WRONLY | (cmd->last_is_double ? O_APPEND : O_TRUNC);
	fd = open(cmd->redir_out_last, flags);
	if (fd < 0)
		errman(NOEXIT, "stdout redirect error");
	return (fd < 0 ? 1 : fd);
}

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
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			errman(NOEXIT, "stdin redirect error");
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
			return (errman(errno, NULL));
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
