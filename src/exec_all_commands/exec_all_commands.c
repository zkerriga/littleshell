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

#include <stdio.h>
int	exec_all_commands(t_list *cmd_list, t_env *env)
{
	int			status;
	t_command	*cmd;

	status = 0;
	while (cmd_list)
	{
		cmd = cmd_list->content;
		if (ft_strncmp(cmd->cmd_name, "env", 4) == 0)
		{
			status = env_command(NULL, 0, 1, env);
		}
		printf("+------------+\n| cmd -> %s\n| status -> %d\n+------------+\n", cmd->cmd_name, status);
		cmd_list = cmd_list->next;
	}
	return (0);
}