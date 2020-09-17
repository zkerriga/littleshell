/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 11:17:43 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/17 11:17:44 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtin_functions.h"

int		pwd_command(char **args, int fdin, int fdout, t_env *env)
{
	const int	pwd_error_code = 1;
	const int	success_code = 0;
	char		*path;
	int			unused;

	unused = fdin || env || args;
	if (!(path = getcwd(NULL, 0)))
	{
		write_err("pwd", NULL, strerror(errno));
		return (pwd_error_code);
	}
	write(fdout, path, ft_strlen(path));
	write(fdout, "\n", 1);
	free(path);
	return (success_code);
}
