/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_work_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:13:18 by matrus            #+#    #+#             */
/*   Updated: 2020/09/15 13:13:21 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_word_work.h"
#include "libft.h"

static char	*parse_key(char *str)
{
	char	*key_start;
	char	*key;

	key_start = str;
	if (ft_isalpha(*str) || *str == '_')
	{
		++str;
		while (ft_isalnum(*str) || *str == '_')
			++str;
		if ((key = (char *)malloc(sizeof(*key) * (str - key_start + 1))))
			ft_strlcpy(key, key_start, str - key_start + 1);
		return (key);
	}
	return (ft_strdup(""));
}

int			word_work_expand(t_word_work *self, char *str, t_env *env)
{
	size_t		shift;
	char		*key;
	const char	*value;

	shift = 1;
	key = NULL;
	if (*++str == '?')
	{
		key = ft_itoa(env->get_status(env)); //TODO: malloc
		value = (const char *)key;
	}
	else
	{
		key = parse_key(str); //TODO: malloc
		shift = ft_strlen(key);
		value = env->get_value(env, (const char*)key);
	}
	while (value && *value)
	{
		self->add_char(self, *value++);
	}
	free(key);
	return (shift);
}
