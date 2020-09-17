/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 08:18:40 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/16 08:18:41 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include <errno.h>

/*
** The command prints an unsorted list of environment variables
** and returns 0 if successful. If an error occurs, returns 126.
*/

int		env_command(char **args, int fdin, int fdout, t_env *env)
{
	const int	env_error_code = 126;
	const int	success_code = 0;
	int			unused;

	unused = args || fdin;
	if (!env)
		return (errno = env_error_code);
	env->print(env, fdout); //TODO: не хватает проверки ошибок с дескриптором
	return (success_code);
}
