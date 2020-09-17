/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_work_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:08:09 by matrus            #+#    #+#             */
/*   Updated: 2020/09/15 13:08:11 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hidden_word_work.h"

void		word_work_delete(t_word_work *self)
{
	if (self->word)
		free(self->word);
	free(self);
}
