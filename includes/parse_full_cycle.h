/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_full_cycle.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 15:03:20 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/19 15:03:21 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_FULL_CYCLE_H
# define PARSE_FULL_CYCLE_H

# include "libft.h"
# include "environment.h"
# include "word_work.h"

typedef struct	s_quotes
{
	int			quote;
	int			d_quote;
}				t_quotes;

int				is_redirect_next(char *str);
int				is_redirect(char ch);

int				begin_into_block(t_word_work *w_work,
									char **str, char *str_start);
void			end_block(t_word_work *w_work, char **str,
							t_quotes *q, t_env *env);
void			slash_slash_block(t_word_work *w_work, char **str, t_quotes *q);

#endif
