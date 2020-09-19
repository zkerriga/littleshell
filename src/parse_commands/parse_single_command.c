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
#include "error_manager.h"

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

typedef struct	s_quotes
{
	int			quote;
	int			d_quote;
}				t_quotes;

static void	slash_slash_block(t_word_work *word_work, char **str, t_quotes *q)
{
	if (q->quote)
		word_work->add_char(word_work, **str);
	else if (q->d_quote)
	{
		if (*(*str + 1) == '$' || *(*str + 1) == '"'
			|| *(*str + 1) == '>' || *(*str + 1) == '<')
		{
			++(*str);
		}
		word_work->add_char(word_work, **str);
	}
	else
	{
		++(*str);
		word_work->add_char(word_work, **str);
	}
}

static char	*get_shell_word_and_go_next(char **str, t_env *env)
{
	t_quotes	q;
	char		*str_start;
	char		*word;
	t_word_work	*word_work;

	ft_bzero(&q, sizeof(q));
	word_work = word_work_new();
	while (ft_isspace(**str))			// Probably might be deleted
		++(*str);
	str_start = *str;
	while (**str)
	{
		if (is_redirect(**str) && !(q.d_quote || q.quote))
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
		else if (ft_isspace(**str) && !(q.d_quote || q.quote))
		{
			++(*str);
			break ;
		}
		else if (**str == '\'' && !q.d_quote)
			q.quote = !q.quote;
		else if (**str == '"' && !q.quote)
			q.d_quote = !q.d_quote;
		else if (**str == '\\')
			slash_slash_block(word_work, str, &q);
		else if (!q.quote && **str == '$' && (ft_isalpha(*(*str + 1)) || *(*str + 1) == '_' || *(*str + 1) == '?'))
			(*str) += word_work->expand(word_work, *str, env);
		else
			word_work->add_char(word_work, **str);
		++(*str);
	}
	if (!(word = ft_strdup(word_work->ret_word(word_work))))
		errman(ENOMEM, NULL);
	word_work->delete(word_work);
	return (word);
}

static char	**shell_word_split_with_env(char *str, t_env *env)
{
	char	**tab_word;
	int		i_word;

	if (!(tab_word = (char**)malloc(sizeof(char*))))
		errman(ENOMEM, NULL);
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
			}
			i_word++;
			if (!(tab_word = (char **)ft_realloc_tab((void **)tab_word, i_word, i_word + 1)))
				errman(ENOMEM, NULL);
		}
	}
	return (tab_word);
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
	}
	else
	{
		free(tab_word);
		cmd->is_empty = 1;
	}
}
