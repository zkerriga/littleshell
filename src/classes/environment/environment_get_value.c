/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_get_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 19:28:19 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/14 19:28:21 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_environment.h"
#include "libft.h"

/*
** Returns the value by key. If there is no value, returns NULL.
** NULL is also returned in case of an error (you need to check errno).
*/

const char	*environment_get_value(t_env *self, const char *key)
{
	char		**tab;
	const char	*value;
	size_t		len;

	if (!(tab = self->_env_array))
		return (NULL);
	value = NULL;
	len = ft_strlen(key);
	if (len)
	{
		while (*tab)
		{
			if (!ft_strncmp(key, *tab, len) && (*tab)[len] == '=')
			{
				value = &((*tab)[len + 1]);
				break ;
			}
			++tab;
		}
	}
	return (value);
}
