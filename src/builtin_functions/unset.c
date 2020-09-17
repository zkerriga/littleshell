/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:31:22 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/16 11:31:24 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtin_functions.h"

static int	is_valid_arg(char *arg)
{
	if (!ft_isalpha(*arg) && *arg != '_')
		return (0);
	++arg;
	while (*arg)
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			return (0);
		++arg;
	}
	return (1);
}

/*
** The function attempts to delete the environment variable.
** The parameter must contain only certain characters,
** otherwise an error is returned (the error code is 1).
*/

int			unset_command(char **args, int fdin, int fdout, t_env *env)
{
	const int	unset_error_code = 1;
	int			status;
	int			unused;

	unused = fdout || fdin;
	if (!env)
		return (errno = unset_error_code);
	status = 0;
	while (*++args)
	{
		if (!is_valid_arg(*args))
		{
			status = unset_error_code;
			write_err("unset", *args, "not a valid identifier");
		}
		else
		{
			env->remove(env, *args);
		}
	}
	return (status ? errno = unset_error_code : status);
}
