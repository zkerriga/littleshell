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
	char 	*key;

	key_start = str;
	if (ft_isalpha(*str) || *str == '_')
	{
		++str;
		while (ft_isalnum(*str) || *str == '_')
			++str;
		key = (char *)malloc(sizeof(*key) * (str - key_start + 1));
		ft_strlcpy(key, key_start, str - key_start + 1);
		return (key);
	}
	return (ft_strdup(""));
}

int			word_work_expand(t_word_work *self, char *str, t_env *env)
{
	int			shift;
	char		*key;
	const char	*value;

	shift = 0;
	str++;
	key = parse_key(str);
	shift += ft_strlen(key);
	value = env->get_value(env, (const char*)key);
	while (value && *value)
	{
		self->add_char(self, *value);
		++value;
	}
	free(key);
	return (shift);
}
