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


/*
**	Just return line from user.
**	No error manag
 * CHAR BY CHAR FUNCTIOIN
 */

#include <signal.h>
#include <stdio.h>

void	sgihand(int sig)
{
	if (sig)
		printf("I got siginfo!\n");
}

int		is_read_ok(char ch, char **line, int *len)
{
	if (ch == '\n')
		return (0);
	if (ft_isprint(ch) || ft_isspace(ch))
	{
		if (!(*line = ft_realloc(*line, *len + 1,
								 *len + 2))) // TODO: add err managementx
			exit(1);
		(*line)[(*len)++] = ch;
		(*line)[*len] = '\0';
	}
	return (1);
}

char	*read_line(void)
{
	char	*line;
	int 	len;
	int		ret;
	char	ch;

	signal(SIGINFO, sgihand);
	len = 0;
	if (!(line = ft_strdup("\0")))
		exit(1);
	while (1)
	{
		ch = '\0';
		if (!g_sigint)
			ret = read(0, &ch, 1);
		else
			break ;
		if (ret == 0 && len == 0)
		{
			free(line);
			line = ft_strdup("exit");		// TODO: add error mgt
			break ;
		}
		if (is_read_ok(ch, &line, &len))
			continue;
		else
			break;
	}
	return (line);
}