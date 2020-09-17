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
#include "builtin_functions.h"
#include "exec_all_commands.h"
#include "get_next_line.h"

//
#include <errno.h>
#include <stdlib.h>

static void	print_execution_result(int fd_from, int fd_to)
{
	int		gnl_status;
	char	*line;

	while ((gnl_status = get_next_line(fd_from, &line)) >= 0)
	{
		write(fd_to, line, ft_strlen(line));
		ft_putendl_fd("", fd_to);
		if (!gnl_status)
			break ;
	}
	printf("errno: %i\n", errno);
}

int			execute_command(t_func_ptr builtin, t_command *cmd, t_env *env)
{
	static int	prev_fd = 0;
	static int	next_fd = 1;
	pid_t		pid;
	int			status;
	int			fildes[2];

	if ((pipe(fildes)) < 0)
		ft_putendl_fd("pipe error", 1); // TODO: error managment ERRNO

	status = 1;

	//	check if builtin
	if (builtin)
	{
		status = builtin(cmd->args, prev_fd, fildes[1], env);
		if (cmd->next_operator[0] == ';' || cmd->next_operator[0] == '\0')
		{
			print_execution_result(fildes[0], 1 /* field to redir to*/);
			close(fildes[0]);
			prev_fd = 0;
			next_fd = 1;
		}

		// close fd need to think
		return status;
	}

	pid = fork();
	if (pid == 0)
	{
		// Child here

		// Make redirects in
		dup2(prev_fd, 0);
		dup2(fildes[1], 1);
		// Exec smth
		status = execve(cmd->cmd_name, cmd->args, env->transfer_control(env));
		// If Error -> write smth;
		ft_putendl_fd("Oops! Bad execution:(", 1);	// TODO: think about error and fd 2
		exit(status);
	}
	else if (pid < 0)
	{
		// Fork error here
		ft_putendl_fd("Forking error", 1); // TODO: error fd 2
	}
	else
	{
		// Parent here
		waitpid(pid, &status, WUNTRACED);
	}

	// After execution part
	if (prev_fd > 0)
		close(prev_fd);
	prev_fd = fildes[0];
	close(fildes[1]);

	// Make redirects out
	// If next command not pipe - reset fds;
	if (cmd->next_operator[0] == ';' || cmd->next_operator[0] == '\0')
	{
		print_execution_result(fildes[0], 1 /* field to redir to*/);
		close(fildes[0]);
		prev_fd = 0;
		next_fd = 1;
	}
	return (status);
}