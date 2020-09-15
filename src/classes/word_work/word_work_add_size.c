/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_work_add_size.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:33:31 by matrus            #+#    #+#             */
/*   Updated: 2020/09/15 13:33:32 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_word_work.h"
#include "get_next_line.h" //TODO: move ft_realloc to libft

void 	word_work_add_size(t_word_work *self)
{
	self->w_max_len += SHELL_WORD_LEN;
	self->word = ft_realloc(self->word, self->w_max_len, self->w_max_len);
}