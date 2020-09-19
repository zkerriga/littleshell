/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_cycle_is_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 15:05:42 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/19 15:05:42 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_redirect_next(char *str)
{
	while (*str && ft_isspace(*str))
		++str;
	if (*str == '>' || *str == '<' || *str == '\0')
		return (1);
	return (0);
}

int	is_redirect(char ch)
{
	if (ch == '<' || ch == '>')
		return (1);
	return (0);
}
