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
#include "word_work.h"
#include <stdlib.h>

//
#include <stdio.h>

char *get_shell_word_and_go_next(char **str, t_env *env)
{
	int			quote;
	int			d_quote;
	char		*word;
	t_word_work	*word_work;

	quote = 0;
	d_quote = 0;
	word_work = word_work_new();
	while (ft_isspace(**str))
		++(*str);
	while (**str)
	{
		if (ft_isspace(**str) && !(d_quote || quote))
		{
			++(*str);
			break;
		}
		if (**str == '\'' && !d_quote)
			quote = !quote;
		else if (**str == '"' && !quote)
			d_quote = !d_quote;
		else if (**str == '\\')
		{
			if (quote)
				word_work->add_char(word_work, **str);
			else if (d_quote)
			{
				if (*(*str + 1) == '$' || *(*str + 1) == '"')
					++(*str);
				word_work->add_char(word_work, **str);
			}
			else
			{
				++(*str);
				word_work->add_char(word_work, **str);
			}
		}
		else if (**str == '$' && (ft_isalpha(*(*str + 1)) || *(*str + 1) == '_'))
			(*str) += word_work->expand(word_work, *str, env);
		else
			word_work->add_char(word_work, **str);
		++(*str);
	}
	word = ft_strdup(word_work->ret_word(word_work));
	word_work->delete(word_work);
	return (word);
}


char **shell_word_split_with_env(char *str, t_env *env)
{
	char	**tab_word;
	int		i_word;

	tab_word = (char**)malloc(sizeof(char*));
	*tab_word = NULL;
	i_word = 0;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (*str)
		{
			tab_word[i_word] = get_shell_word_and_go_next(&str, env);	// TODO: mignt be malloc error
			i_word++;
			if (!(tab_word = (char **)ft_realloc_tab((void **)tab_word, i_word, i_word + 1)))
				printf("Malloc error in shell_word_split_with_env\n"); // TODO: error check
		}
	}
	return (tab_word);
}

void parse_single_command(char *cmd_str, t_command *cmd, t_env *env)
{
	char	**tab_word;

	tab_word = shell_word_split_with_env(cmd_str, env);
	cmd->redir_in = parse_redirection(&tab_word, "<");

	// Here we should fill redirects



	//	here we should set cmd fields
	if (*tab_word)
	{
		cmd->args = tab_word;
		cmd->cmd_name = ft_strdup(tab_word[0]);
	}

	// TEST
	char	**i_tab_word;
	i_tab_word = tab_word;
	while (*i_tab_word)
	{
		printf("|%s", *i_tab_word ? *i_tab_word : "null!");
		++i_tab_word;
	}
	printf("\n\n");
	// END TEST
}

