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
#include "builtin_functions.h"
#include "exec_all_commands.h"

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
	int				i;
	const t_cmdlink	cmd_links[] = {{"env", env_command},
{"unset", unset_command}, {"export", export_command}, {"exit", exit_command},
{"echo", echo_command}, {"cd", cd_command}, {"pwd", pwd_command},
{NULL, NULL}};

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

int					exec_one_command(t_command *cmd, t_env *env)
{
	int				status;
	t_func_ptr		cmd_link;

	if ((status = open_output_redirects(cmd) + check_input_redirects(cmd)))
		return (status);
	cmd_link = if_builtins_get_function(cmd->cmd_name);
	if (!cmd_link && !is_ok_set_cmd_exec_name(cmd, env))
	{
		status = 127;
		write_err(cmd->cmd_name, NULL, "no such command");
	}
	else
		status = execute_command(cmd_link, cmd, env);
	return (status);
}
