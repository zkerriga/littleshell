/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 17:24:47 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/14 18:58:00 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hidden_environment.h"

void	environment_del(t_env *self)
{
	ft_free_tab((void **)self->env_array);
	free(self);
}
