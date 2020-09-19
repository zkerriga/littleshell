/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 17:27:14 by matrus            #+#    #+#             */
/*   Updated: 2020/09/12 17:27:15 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_commands.h"
#include "environment.h"

/*
**	Parse command from *cmd_line till separate char (';' or '|'), then
**	shift *cmd_line to next command, then
**	write parsed information into *cmd, then
**	return modified *cmd_line;
*/

char	*parse_first_cmd_and_go_next(char *cmd_line,
										t_command *cmd, t_env *env)
{
	char	*cur_cmd_line;

	cur_cmd_line = cmd_line;
	while (*cmd_line && !does_command_separates(&cmd_line))
		cmd_line++;
	set_separator_type(&cmd_line, cmd);
	if (*cmd_line)
	{
		*cmd_line = '\0';
		cmd_line++;
	}
	parse_single_command(cur_cmd_line, cmd, env);
	return (cmd_line);
}
