/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_transfer_control.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 19:28:57 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/14 19:28:59 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hidden_environment.h"

char	**environment_transfer_control(t_env *self)
{
	return (self->env_array);
}
