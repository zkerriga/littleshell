/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_all_commands.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 17:23:57 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/12 17:24:00 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_ALL_COMMANDS_H
# define EXEC_ALL_COMMANDS_H

# include "libft.h"
# include "environment.h"

int	exec_all_commands(t_list *cmd_list, t_env *env);

#endif
