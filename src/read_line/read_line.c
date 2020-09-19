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

/*
** CHAR BY CHAR FUNCTION
*/

int		is_read_ok(char ch, char **line, int *len)
{
	if (ch == '\n')
		return (0);
	if (ch != '\0')
	{
		if (!(*line = ft_realloc(*line, *len + 1, *len + 2)))
			errman(ENOMEM, NULL);
		(*line)[(*len)++] = ch;
		(*line)[*len] = '\0';
	}
	return (1);
}

char	*read_line(void)
{
	char	*line;
	int		len;
	int		ret;
	char	ch;

	len = 0;
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
		if (is_read_ok(ch, &line, &len))
			continue ;
		else
			break ;
	}
	return (line);
}