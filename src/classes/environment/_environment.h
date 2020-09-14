/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _environment.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 16:48:40 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/14 16:48:50 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ENVIRONMENT_H
# define _ENVIRONMENT_H

# include "libft.h"

typedef struct	s_env
{
	int			(*add)(struct s_env *self, char *key, char *value);
	void		(*remove)(struct s_env *self, char *key);
	void		(*print)(struct s_env *self, int fd);
	char		*(*get_value)(struct s_env *self, char *key);
	char		**(*transfer_control)(struct s_env *self);
	void		(*del)(struct s_env *self);
	char		**__env_array;
}				t_env;

t_env			*environment_new(char **envp);
void			environment_del(t_env *self);

#endif
