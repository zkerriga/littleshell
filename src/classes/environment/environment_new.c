/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:24:30 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/14 17:24:34 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_environment.h"

static int	envp_is_valid(const char **envp)
{
	while (*envp)
	{
		if (!ft_strchr(*envp++, '='))
			return (0);
	}
	return (1);
}

/*
** Class constructor. Returns NULL if an error occurs.
*/

t_env	*environment_new(const char **envp)
{
	t_env	*self;

	if (!envp_is_valid(envp))
		return (NULL);
	if ((self = ft_calloc(sizeof(t_env), 1)))
	{
		if ((self->_env_array = ft_tabdub(envp)))
		{
			self->add = NULL;
			self->remove = NULL;
			self->print = NULL;
			self->get_value = get_value;
			self->transfer_control = NULL;
			self->del = environment_del;
		}
		else
		{
			free(self);
			self = NULL;
		}
	}
	return (self);
}
