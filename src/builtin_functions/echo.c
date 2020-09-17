/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 09:39:20 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/17 09:39:22 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

int		echo_command(char **args, int fdin, int fdout, t_env *env)
{
	const int	success_code = 0;
	int			set_enter_flag;
	int			unused;

	unused = fdin || env;
	set_enter_flag = args[1] ? ft_strncmp(args[1], "-n", 3) : 1;
	args = set_enter_flag ? args : args + 1;
	while (*++args)
	{
		write(fdout, *args, ft_strlen(*args));
		if (args[1])
			write(fdout, " ", 1);
	}
	if (set_enter_flag)
		write(fdout, "\n", 1);
	return (success_code);
}
