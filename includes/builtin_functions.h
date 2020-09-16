/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 17:23:37 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/12 17:23:41 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_FUNCTION_H
# define BUILTIN_FUNCTION_H

# include "environment.h"

int		env_command(char **args, int stdin, int stdout, t_env *env);

#endif
