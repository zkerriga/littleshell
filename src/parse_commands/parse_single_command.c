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

static int	is_redirect_next(char *str)
{
	while (*str && ft_isspace(*str))
		++str;
	if (*str == '>' || *str == '<' || *str == '\0')
		return (1);
	return (0);
}

static int	is_redirect(char ch)
{
	if (ch == '<' || ch == '>')
		return (1);
	return (0);
}

static char	*get_shell_word_and_go_next(char **str, t_env *env)
{
	int			quote;
	int			d_quote;
	char		*str_start;
	char		*word;
	t_word_work	*word_work;

	quote = 0;
	d_quote = 0;
	word_work = word_work_new();
	while (ft_isspace(**str))			// Probably might be deleted
		++(*str);
	str_start = *str;
	while (**str)
	{
		if (is_redirect(**str) && !(d_quote || quote))
		{
			if (str_start == *str)
			{
				word_work->add_char(word_work, **str);
				++(*str);
				if (is_redirect(**str))
				{
					word_work->add_char(word_work, **str);
					++(*str);
				}
				if (is_redirect_next(*str))
				{
					word_work->delete(word_work);
					return (NULL);
				}
			}
			break ;
		}
		else if (ft_isspace(**str) && !(d_quote || quote))
		{
			++(*str);
			break ;
		}
		else if (**str == '\'' && !d_quote)
			quote = !quote;
		else if (**str == '"' && !quote)
			d_quote = !d_quote;
		else if (**str == '\\')
		{
			if (quote)
				word_work->add_char(word_work, **str);
			else if (d_quote)
			{
				if (*(*str + 1) == '$' || *(*str + 1) == '"' || *(*str + 1) == '>' || *(*str + 1) == '<')
					++(*str);
				word_work->add_char(word_work, **str);
			}
			else
			{
				++(*str);
				word_work->add_char(word_work, **str);
			}
		}
		else if (!quote && **str == '$' && (ft_isalpha(*(*str + 1)) || *(*str + 1) == '_' || *(*str + 1) == '?'))
			(*str) += word_work->expand(word_work, *str, env);
		else
			word_work->add_char(word_work, **str);
		++(*str);
	}
	word = ft_strdup(word_work->ret_word(word_work));
	word_work->delete(word_work);
	return (word);
}

static char	**shell_word_split_with_env(char *str, t_env *env)
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
			if (!(tab_word[i_word] = get_shell_word_and_go_next(&str, env)))
			{
				ft_free_tab((void **)tab_word);
				return (NULL);
			}// TODO: mignt be malloc error
			i_word++;
			if (!(tab_word = (char **)ft_realloc_tab((void **)tab_word, i_word, i_word + 1)))
				ft_putendl_fd("Malloc error in shell_word_split_with_env", 1); // TODO: error check
		}
	}
	return (tab_word);
}

void		parse_single_command(char *cmd_str, t_command *cmd, t_env *env)
{
	char	**tab_word;

	if (!(tab_word = shell_word_split_with_env(cmd_str, env)))
	{
		ft_putendl_fd("Parse error!", 1); // TODO: add normal error msg
		cmd->is_empty = 1;
		return ;
	}
	if (*tab_word)
	{
		cmd->redir_out_last = find_last_redir_out(tab_word);
		cmd->redir_in_app = parse_redirection(tab_word, "<<");
		cmd->redir_out_app = parse_redirection(tab_word, ">>");
		cmd->redir_in = parse_redirection(tab_word, "<");
		cmd->redir_out = parse_redirection(tab_word, ">");
		cmd->args = tab_word;
		cmd->cmd_name = (*tab_word) ? ft_strdup(tab_word[0]) : ft_strdup("");	// TODO: add error managment
	}
	else
	{
		free(tab_word);
		cmd->is_empty = 1;
	}
}
