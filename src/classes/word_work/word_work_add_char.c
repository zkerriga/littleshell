/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_work_add_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:13:15 by matrus            #+#    #+#             */
/*   Updated: 2020/09/15 13:13:17 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_word_work.h"

void		word_work_add_char(t_word_work *self, char ch)
{
	if (self->w_len + 2 >= self->w_max_len)
		self->add_size(self);
	self->word[self->w_len] = ch;
	self->word[self->w_len + 1] = '\0';
	++(self->w_len);
}
