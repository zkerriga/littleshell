/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_word_split_with_env.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 14:57:17 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/19 14:57:19 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_commands.h"
#include "environment.h"
#include "word_work.h"
#include "error_manager.h"
#include "parse_full_cycle.h"

static int	full_cycle(t_word_work *w_work, char **str, t_quotes *q, t_env *env)
{
	char	*str_start;

	str_start = *str;
	while (**str)
	{
		if (is_redirect(**str) && !(q->d_quote || q->quote))
		{
			if (begin_into_block(w_work, str, str_start))
				return (1);
			break ;
		}
		else if (ft_isspace(**str) && !(q->d_quote || q->quote))
		{
			++(*str);
			break ;
		}
		else
			end_block(w_work, str, q, env);
		++(*str);
	}
	return (0);
}

static char	*get_shell_word_and_go_next(char **str, t_env *env)
{
	t_quotes	q;
	char		*word;
	t_word_work	*word_work;

	ft_bzero(&q, sizeof(t_quotes));
	word_work = word_work_new();
	while (ft_isspace(**str))
		++(*str);
	if (full_cycle(word_work, str, &q, env))
		return (NULL);
	if (!(word = ft_strdup(word_work->ret_word(word_work))))
		errman(ENOMEM, NULL);
	word_work->delete(word_work);
	return (word);
}

char		**shell_word_split_with_env(char *str, t_env *env)
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
			if (!(tab_word = (char **)ft_realloc_tab((void **)tab_word,
														i_word, i_word + 1)))
				errman(ENOMEM, NULL);
		}
	}
	return (tab_word);
}
