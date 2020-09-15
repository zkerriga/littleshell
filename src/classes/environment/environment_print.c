/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 19:28:02 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/14 19:28:05 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_environment.h"

void	environment_print(t_env *self, int fd)
{
	char	**env_tab;

	env_tab = self->_env_array;
	while (*env_tab)
	{
		write(fd, *env_tab, ft_strlen(*env_tab));
		write(fd, "\n", 1);
		++env_tab;
	}
}
