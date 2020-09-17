/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 10:31:58 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/17 10:32:00 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtin_functions.h"

int		cd_command(char **args, int fdin, int fdout, t_env *env)
{
	const int	cd_error_code = 1;
	const int	success_code = 0;
	int			unused;

	unused = fdin || fdout || env;
	if (!args[1])
		return (errno = cd_error_code);
	if (chdir(args[1]) < 0)
	{
		write_err("cd", args[1], strerror(errno));
		return (cd_error_code);
	}
	return (success_code);
}
