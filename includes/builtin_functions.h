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
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <dirent.h>

int		env_command(char **args, int fdin, int fdout, t_env *env);
int		unset_command(char **args, int fdin, int fdout, t_env *env);
int		export_command(char **args, int fdin, int fdout, t_env *env);
int		exit_command(char **args, int fdin, int fdout, t_env *env);
int		echo_command(char **args, int fdin, int fdout, t_env *env);
int		cd_command(char **args, int fdin, int fdout, t_env *env);
int		pwd_command(char **args, int fdin, int fdout, t_env *env);

void	write_err(char *cmd_name, char *trouble_str, char *description);

#endif
