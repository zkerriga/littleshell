/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_cycle_blocks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 15:07:28 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/19 15:07:29 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_full_cycle.h"

void	slash_slash_block(t_word_work *w_work, char **str, t_quotes *q)
{
	if (q->quote)
		w_work->add_char(w_work, **str);
	else if (q->d_quote)
	{
		if (*(*str + 1) == '$' || *(*str + 1) == '"'
			|| *(*str + 1) == '>' || *(*str + 1) == '<')
		{
			++(*str);
		}
		w_work->add_char(w_work, **str);
	}
	else
	{
		++(*str);
		w_work->add_char(w_work, **str);
	}
}

void	end_block(t_word_work *w_work, char **str, t_quotes *q, t_env *env)
{
	if (**str == '\'' && !q->d_quote)
		q->quote = !q->quote;
	else if (**str == '"' && !q->quote)
		q->d_quote = !q->d_quote;
	else if (**str == '\\')
		slash_slash_block(w_work, str, q);
	else if (!q->quote && **str == '$' && (ft_isalpha(*(*str + 1))
										   || *(*str + 1) == '_' || *(*str + 1) == '?'))
	{
		(*str) += w_work->expand(w_work, *str, env);
	}
	else
		w_work->add_char(w_work, **str);
}

int		begin_into_block(t_word_work *w_work, char **str, char *str_start)
{
	if (str_start == *str)
	{
		w_work->add_char(w_work, **str);
		++(*str);
		if (is_redirect(**str))
		{
			w_work->add_char(w_work, **str);
			++(*str);
		}
		if (is_redirect_next(*str))
		{
			w_work->delete(w_work);
			return (1);
		}
	}
	return (0);
}
