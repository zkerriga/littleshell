/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_print_sorted.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 13:57:27 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/16 13:57:28 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_environment.h"
#include "libft.h"

static int	env_compare(void *env1, void *env2)
{
	size_t	len1;

	len1 = ft_strlen(env1);
	return (ft_strncmp(env1, env2, len1 + 1));
}

static char	**sort_tab(char **tab, size_t size, int (*cmp)(void *, void *))
{
	size_t	i;
	size_t	j;
	char	*swap;

	i = -1;
	while (++i < size)
	{
		j = size;
		while (--j >= i + 1)
		{
			if (cmp(tab[j], tab[j - 1]) < 0)
			{
				swap = tab[j];
				tab[j] = tab[j - 1];
				tab[j - 1] = swap;
			}
		}
	}
	return (tab);
}

void	environment_print_sorted(t_env *self, int fd)
{
	char	**env_tab;
	char	**save_ptr;

	env_tab = ft_tabdub((const char **)self->_env_array);
	save_ptr = env_tab;
	env_tab = sort_tab(env_tab, self->len, env_compare);
	while (*env_tab)
	{
		write(fd, "declare -x ", 11);
		write(fd, *env_tab, ft_strlen(*env_tab));
		write(fd, "\n", 1);
		++env_tab;
	}
	free(save_ptr);
}
