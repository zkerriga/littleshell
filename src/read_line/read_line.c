/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:32:04 by matrus            #+#    #+#             */
/*   Updated: 2020/09/12 15:32:14 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include "minishell.h"
#include "error_manager.h"

int		is_read_ok(char ch, char **line, int *len)
{
	if (ch == '\n')
		return (0);
	if (ft_isprint(ch) || ft_isspace(ch))
	{
		if (!(*line = ft_realloc(*line, (*len) + 2, (*len) + 1)))
			errman(ENOMEM, NULL);
		(*line)[(*len)++] = ch;
		(*line)[*len] = '\0';
	}
	return (1);
}

static void	clear_metachar_d()
{
	write(1, "  \b\b", 4);
}

char	*read_line(void)
{
	char	*line;
	int		len;
	int		ret;
	char	ch;

	len = 0;
	g_isread = 1;
	if (!(line = ft_strdup("\0")))
		errman(ENOMEM, NULL);
	while (1)
	{
		ch = '\0';
		ret = read(0, &ch, 1);
		if (ret == 0 && len == 0)
		{
			free(line);
			if (!(line = ft_strdup("exit")))
				errman(ENOMEM, NULL);
			break ;
		}
		if (ret == 0)
			clear_metachar_d();
		if (!is_read_ok(ch, &line, &len))
			break ;
	}
	g_isread = 0;
	return (line);
}
