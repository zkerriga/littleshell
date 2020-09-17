/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_work_ret_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:13:25 by matrus            #+#    #+#             */
/*   Updated: 2020/09/15 13:13:26 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hidden_word_work.h"

const char	*word_work_ret_word(t_word_work *self)
{
	return ((const char*)self->word);
}
