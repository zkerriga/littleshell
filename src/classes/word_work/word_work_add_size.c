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

#include "hidden_word_work.h"
#include "get_next_line.h"
#include "error_manager.h"

void	word_work_add_size(t_word_work *self)
{
	self->word = ft_realloc(self->word, self->w_max_len
		+ SHELL_WORD_LEN, self->w_max_len);
	self->w_max_len += SHELL_WORD_LEN;
	if (!self->word)
		errman(ENOMEM, NULL);
}
