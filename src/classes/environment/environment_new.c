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

/*
** Class constructor. Returns NULL if an error occurs.
*/

t_env	*environment_new(char **envp)
{
	t_env	*self;

	if ((self = ft_calloc(sizeof(t_env), 1)))
	{
		if ((self->__env_array = ft_tabdub(envp)))
		{
			self->add = NULL;
			self->remove = NULL;
			self->print = NULL;
			self->get_value = NULL;
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
