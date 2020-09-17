/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <zkerriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 19:27:31 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/14 19:27:34 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_environment.h"
#include "libft.h"

static char	*create_env_string(const char *key, const char *value)
{
	char	*env_str;
	size_t	key_len;
	size_t	value_len;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	if ((env_str = (char *)malloc(sizeof(char) * (key_len + value_len + 2))))
	{
		ft_strlcpy(env_str, key, key_len + 1);
		env_str[key_len] = '=';
		ft_strlcpy(&(env_str[key_len + 1]), value, value_len + 1);
	}
	return (env_str);
}

static void	*ft_specalloc(void *ptr, size_t prev_size, size_t new_size)
{
	void	*new_memory;

	if ((new_memory = malloc(new_size)))
	{
		ft_memmove(new_memory, ptr, prev_size);
		free(ptr);
	}
	return (new_memory);
}

static int	if_exist_add_into(t_env *self, const char *key, char *new_env_str)
{
	char	**env_tab;
	size_t	key_len;

	env_tab = self->env_array;
	key_len = ft_strlen(key);
	while (*env_tab)
	{
		if (!ft_strncmp(key, *env_tab, key_len) && (*env_tab)[key_len] == '=')
		{
			free(*env_tab);
			*env_tab = new_env_str;
			return (1);
		}
		++env_tab;
	}
	return (0);
}

int			environment_add(t_env *self, const char *key, const char *value)
{
	char	*new_env_str;

	if (!key || !value || !(new_env_str = create_env_string(key, value)))
		return (1);
	if (!if_exist_add_into(self, key, new_env_str))
	{
		self->env_array = ft_specalloc(self->env_array,
										sizeof(char *) * (self->len + 1),
										sizeof(char *) * (self->len + 2));
		if (!self->env_array)
			return (1);
		self->env_array[self->len++] = new_env_str;
		self->env_array[self->len] = NULL;
	}
	return (0);
}
