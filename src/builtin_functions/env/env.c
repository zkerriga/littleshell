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

int		env_command(char **args, int stdin, int stdout, t_env *env)
{
	const int	env_error_code = 126;
	const int	success_code = 0;

	if (args || stdin)
	{
	}
	if (!env)
		return (env_error_code);
	env->print(env, stdout); //TODO: не хватает проверки ошибок с дескриптором
	return (success_code);
}
