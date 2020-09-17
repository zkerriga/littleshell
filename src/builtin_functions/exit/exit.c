/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 08:10:04 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/17 08:10:05 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtin_functions.h"

static int	is_numeric_argument(char *arg)
{
	int		sign_flag;

	sign_flag = 0;
	while (ft_isspace(*arg))
		++arg;
	if (*arg == '-' || *arg == '+')
	{
		sign_flag = 1;
		++arg;
	}
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		sign_flag = 0;
		++arg;
	}
	return (sign_flag ? 0 : 1);
}

int		exit_command(char **args, int fdin, int fdout, t_env *env)
{
	const int	exit_error_code = 1;
	const int	alpha_error_code = 255;
	int			unused;
	int			status;

	unused = fdout || fdin;
	write(2, "exit\n", 6);
	if (!args[1])
	{
		status = env->get_status(env);
	}
	else if (is_numeric_argument(args[1]))
	{
		if (args[2])
		{
			write_err("exit", NULL, "too many arguments");
			return (errno = exit_error_code);
		}
		status = (unsigned char)ft_atoi(args[1]);
	}
	else
	{
		write_err("exit", args[1], "numeric argument required");
		errno = alpha_error_code;
		status = alpha_error_code;
	}
	exit(status);
}
