/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 14:33:36 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/16 14:33:37 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtin_functions.h"

static int	is_valid_arg(char *arg)
{
	if (!(ft_isalpha(*arg) || *arg == '_') || !ft_strchr(arg, '='))
		return (0);
	++arg;
	while (*arg && *arg != '=')
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			return (0);
		++arg;
	}
	return (1);
}

static void	split_and_add(char *env_str, t_env *env)
{
	char		*key;
	const char	*value;
	char		*equal_ptr;

	equal_ptr = ft_strchr(env_str, '='); //TODO: NULL bag
	if (!(key = ft_substr(env_str, 0, equal_ptr - env_str))) //TODO: malloc error
		exit(ENOMEM);
	value = equal_ptr + 1;
	if (env->add(env, key, value))
		exit(ENOMEM); //TODO: error management
	free(key);
}

int		export_command(char **args, int fdin, int fdout, t_env *env)
{
	const int	export_error_code = 1;
	int	status;
	int	unused;

	unused = fdin;
	if (!env)
		return (errno = export_error_code);
	status = 0;
	if (!args[1])
	{
		env->print_sorted(env, fdout); //TODO: нет обработки ошибки маллока
		return (status);
	}
	while (*++args)
	{
		if (!is_valid_arg(*args))
		{
			status = export_error_code;
			write_err("export", *args, "not a valid identifier");
		}
		else
		{
			split_and_add(*args, env);
		}
	}
	return (status ? errno = export_error_code : status);
}
