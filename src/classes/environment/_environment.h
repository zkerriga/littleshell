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
	int			(*add)(struct s_env *self, const char *key, const char *value);
	void		(*remove)(struct s_env *self, const char *key);
	void		(*print)(struct s_env *self, int fd);
	const char	*(*get_value)(struct s_env *self, const char *key);
	char		**(*transfer_control)(struct s_env *self);
	void		(*del)(struct s_env *self);
	char		**_env_array;
	size_t		len;
}				t_env;

t_env			*environment_new(const char **envp);
void			environment_del(t_env *self);
const char		*environment_get_value(t_env *self, const char *key);
char			**environment_transfer_control(t_env *self);
int				environment_add(t_env *, const char *key, const char *value);

#endif
