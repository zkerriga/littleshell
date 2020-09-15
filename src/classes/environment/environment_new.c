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

static size_t	count_environment(const char **envp)
{
	size_t	counter;

	counter = 0;
	while (*envp)
	{
		if (!ft_strchr(*envp++, '='))
			return (0);
		++counter;
	}
	return (counter);
}

/*
** Class constructor. Returns NULL if an error occurs.
*/

t_env			*environment_new(const char **envp)
{
	t_env	*self;
	size_t	len;

	if (!(len = count_environment(envp)))
		return (NULL);
	if ((self = ft_calloc(sizeof(t_env), 1)))
	{
		if ((self->_env_array = ft_tabdub(envp)))
		{
			self->len = len;
			self->add = environment_add;
			self->remove = NULL;
			self->print = NULL;
			self->get_value = environment_get_value;
			self->transfer_control = environment_transfer_control;
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
