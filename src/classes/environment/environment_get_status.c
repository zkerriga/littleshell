/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_get_status.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 08:00:03 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/16 08:00:05 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hidden_environment.h"

int		environment_get_status(t_env *self)
{
	return (self->exit_status);
}
