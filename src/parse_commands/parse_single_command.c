/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_single_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 22:31:54 by matrus            #+#    #+#             */
/*   Updated: 2020/09/14 22:31:55 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_commands.h"
#include "environment.h"
#include "error_manager.h"

static char *string_to_lower(char *str)
{
	char	*save_ptr;

	save_ptr = str;
	while (*str)
	{
		*str = (char)ft_tolower(*str);
		++str;
	}
	return (save_ptr);
}

void		parse_single_command(char *cmd_str, t_command *cmd, t_env *env)
{
	char	**tab_word;

	if (!(tab_word = shell_word_split_with_env(cmd_str, env)))
	{
		errman(NOEXIT, "parse error");
		cmd->is_empty = 1;
		return ;
	}
	if (*tab_word)
	{
		set_last_output_redirect_info(tab_word, cmd);
		cmd->redir_in_app = parse_redirection(tab_word, "<<");
		cmd->redir_out_app = parse_redirection(tab_word, ">>");
		cmd->redir_in = parse_redirection(tab_word, "<");
		cmd->redir_out = parse_redirection(tab_word, ">");
		cmd->args = tab_word;
		if (!(cmd->cmd_name = ft_strdup((*tab_word) ? tab_word[0] : "")))
			errman(ENOMEM, NULL);
		string_to_lower(cmd->cmd_name);
	}
	else
	{
		free(tab_word);
		cmd->is_empty = 1;
	}
}
