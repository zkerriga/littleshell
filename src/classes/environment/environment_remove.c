/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_remove.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 19:27:51 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/14 19:27:53 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hidden_environment.h"
#include "libft.h"

void	environment_remove(t_env *self, const char *key)
{
	char	**env_tab;
	size_t	key_len;

	if (!key)
		return ;
	key_len = ft_strlen(key);
	env_tab = self->env_array;
	while (*env_tab)
	{
		if (!ft_strncmp(key, *env_tab, key_len) && (*env_tab)[key_len] == '=')
		{
			free(*env_tab);
			--(self->len);
			break ;
		}
		++env_tab;
	}
	while (*env_tab)
	{
		*env_tab = *(env_tab + 1);
		++env_tab;
	}
}
