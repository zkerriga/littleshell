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
#include <sys/stat.h>
#include "error_manager.h"

/*
** The command prints an unsorted list of environment variables
** and returns 0 if successful. If an error occurs, returns 126.
*/

int		env_command(char **args, int fdin, int fdout, t_env *env)
{
	struct stat	f_stat;
	const int	env_error_code = 126;
	const int	success_code = 0;
	int			unused;

	unused = args || fdin;
	if (!env)
		return (errno = env_error_code);
	if (fstat(fdout, &f_stat) < 0)
		return (errman(errno, NULL));
	env->print(env, fdout);
	return (success_code);
}
