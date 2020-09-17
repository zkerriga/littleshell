/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 17:46:25 by matrus            #+#    #+#             */
/*   Updated: 2020/09/12 17:46:26 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "builtin_functions.h"
#include "exec_all_commands.h"
#include <stdio.h>

static int			is_equal_cmd_name(const char *const_name, const char *cmd)
{
	while (*const_name && *cmd)
	{
		if (*const_name++ != ft_tolower(*cmd++))
			return (0);
	}
	return (*const_name == *cmd);
}

static t_func_ptr	if_builtins_get_function(char *cmd_name)
{
	const t_cmdlink	cmd_links[] = {{"env", env_command},
{"unset", unset_command}, {"export", export_command},
{"exit", exit_command}, {"echo", echo_command},
{"cd", cd_command}, {NULL, NULL}};
	int				i;

	i = 0;
	while (cmd_links[i].cmd_name)
	{
		if (is_equal_cmd_name(cmd_links[i].cmd_name, cmd_name))
		{
			return (cmd_links[i].func);
		}
		++i;
	}
	return (NULL);
}

int	exec_all_commands(t_list *cmd_list, t_env *env)
{
	int				status;
	t_command		*cmd;
	t_func_ptr		cmd_link;

	status = 0;
	while (cmd_list)
	{
		cmd = cmd_list->content;
		if ((cmd_link = if_builtins_get_function(cmd->cmd_name)))
		{
			status = execute_command(cmd_link, cmd, env);
			cmd_link = NULL;
		}
		else if (is_ok_set_cmd_exec_name(cmd, env))
		{
			status = execute_command(NULL, cmd, env);
			//printf("i will try run: %s\n", cmd->cmd_name);
		}
		else
			printf("no such command:(\n");
		//printf("+------------+\n| cmd -> %s\n| status -> %d\n+------------+\n", cmd->cmd_name, status);
		cmd_list = cmd_list->next;
	}
	return (status);
}
