/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_work_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 11:41:40 by matrus            #+#    #+#             */
/*   Updated: 2020/09/15 11:41:42 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_word_work.h"
#include "libft.h"

t_word_work	*word_work_new(void)
{
	t_word_work *ww_new;

	if(!(ww_new = (t_word_work *)malloc(sizeof(*ww_new))))
		exit(1); // TODO: add error management
	ww_new->ret_word = word_work_ret_word;
	ww_new->add_char = word_work_add_char;
	ww_new->delete = word_work_delete;
	ww_new->expand = word_work_expand;
	ww_new->add_size = word_work_add_size;
	ww_new->word = (char*)malloc(sizeof(*(ww_new->word)) * SHELL_WORD_LEN);
	ft_bzero(ww_new->word, SHELL_WORD_LEN);
	if (!ww_new->word)
		exit(1); // TODO: add error management
	ww_new->w_len = 0;
	ww_new->w_max_len = SHELL_WORD_LEN;
	return (ww_new);
}
