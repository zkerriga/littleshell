/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden_word_work.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 12:01:19 by matrus            #+#    #+#             */
/*   Updated: 2020/09/15 12:01:20 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIDDEN_WORD_WORK_H
# define HIDDEN_WORD_WORK_H

# include "environment.h"
# define SHELL_WORD_LEN 256

typedef struct	s_word_work
{
	void		(*add_char)(struct s_word_work *self, char ch);
	const char	*(*ret_word)(struct s_word_work *self);
	int			(*expand)(struct s_word_work *self, char *str, t_env *env);
	void		(*delete)(struct s_word_work *self);
	char		*word;
	int			cur_pos;
	int			w_len;
	int			w_max_len;
	void		(*add_size)(struct s_word_work *self);
}				t_word_work;

t_word_work		*word_work_new();

int				word_work_expand(t_word_work *self, char *str, t_env *env);
const char		*word_work_ret_word(t_word_work *self);
void			word_work_add_char(t_word_work *self, char ch);
void			word_work_delete(t_word_work *self);
void			word_work_add_size(t_word_work *self);

#endif
