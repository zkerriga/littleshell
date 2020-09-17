/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_work.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:58:41 by matrus            #+#    #+#             */
/*   Updated: 2020/09/15 11:58:42 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORD_WORK_H
# define WORD_WORK_H

# include "environment.h"

typedef struct	s_word_work
{
	void		(*add_char)(struct s_word_work *self, char ch);
	const char	*(*ret_word)(struct s_word_work *self);
	int			(*expand)(struct s_word_work *self, char *str, t_env *env);
	void		(*delete)(struct s_word_work *self);
}				t_word_work;

t_word_work		*word_work_new();

#endif
