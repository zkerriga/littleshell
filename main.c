/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:58:02 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/12 14:58:06 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "read_line.h"
#include "exec_all_commands.h"
#include "parse_commands.h"
#include "environment.h"
#include "clear_command_line.h"

int		execute_line(char *cmd_line, t_env *env)
{
	t_command	cmd;
	int			status;

	status = 0;
	ft_bzero(&cmd, sizeof(cmd));
	while (*cmd_line)
	{
		cmd_line = parse_first_cmd_and_go_next(cmd_line, &cmd, env);
		if (!cmd.is_empty)
			status = exec_one_command(&cmd, env);
	}
	return (status);
}

void	loop(t_env *env)
{
	char	*cmd_line;
	//char	*clean_cmd_line;
	//t_list	*cmd_list;
	int		status;
	char	*current_path;

	status = 1; //TODO: сделать штуку, которая отчистит терминал
	while (status)
	{
		current_path = getcwd(NULL, 0);
		write(1, current_path, ft_strlen(current_path));
		write(1, ": ", 2);
		cmd_line = read_line();
		//clean_cmd_line = clear_command_line(cmd_line);
		//cmd_list = parse_command_line(cmd_line, env);
		//status = exec_all_commands(cmd_list, env);
		status = execute_line(cmd_line, env);
		free(cmd_line);
		//free(clean_cmd_line);
		free(current_path);
		//ft_lstclear(&cmd_list, (void (*)(void*))destroy_command);
		status = 1; // for testing
	}
}

#include <stdio.h>
int		main(int ac, char **av, char **envp)
{
	t_env	*env;

	env = environment_new((const char **)envp);
	if (ac && av)
	{
		loop(env);
	}
	env->del(env);
	return (0);
}
