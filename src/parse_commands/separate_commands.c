/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 21:59:09 by matrus            #+#    #+#             */
/*   Updated: 2020/09/14 21:59:12 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_command_separator(const char *line)
{
	if (line[0] == '|')
		return (1);
	if (line[0] == ';')
		return (1);
	return (0);
}

/*
**	Returns 1 if command separator found in *cmd_line given quotation marks;
**	If '\' occurs, function moves ptr of *cmd_line skipping that backslash.
**	Returns 0 otherwise.
*/

int does_command_separates(char **cmd_line, int *was_quote, int *was_d_quote)
{
	if ((!(*was_quote || *was_d_quote) &&
		is_command_separator(*cmd_line)) ||
		(**cmd_line == '\\' && *(*cmd_line + 1) == '\0'))
	{
		return (1);
	}
	if (**cmd_line == '\\')
	{
		(*cmd_line)++;
		return (0);
	}
	if (**cmd_line == '\'' && !*was_d_quote)
		*was_quote = !(*was_quote);
	if (**cmd_line == '\"' && !(*was_quote))
		*was_d_quote = !(*was_d_quote);
	return (0);
}

/*
**	Sets cmd->next_operator;
**	if separator contains 2 chars, shifts ptr *cmd_line by 1
*/

void			set_separator_type(char **cmd_line, t_command *cmd)
{
	cmd->next_operator[0] = '\0';
	cmd->next_operator[1] = '\0';
	if (**cmd_line == '\\')
		;
	else if (**cmd_line == ';')
		cmd->next_operator[0] = ';';
	else if (**cmd_line == '|')
		cmd->next_operator[0] = '|';
}
