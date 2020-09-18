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
**	No error management
*/

//char	*read_line(void)
//{
//	char	*line;
//	int		fd;
//	int		i;
//
//	line = NULL;
//	line = calloc(100000, 1);
//	fd = dup(0);
//	i = 0;
//	while (1)
//	{
//		read(fd, &(line[i]), 1);
//		printf("%s\n", line);
//		if (line[i] == '\n')
//		{
//			line[i] = '\0';
//			break;
//		}
//		else if (line[i] == 4)
//		{
//			printf("I wrote to stdin\n");
//			write(0, line, strlen(line));
//			continue ;
//		}
//		else
//			i++;
//	}
//	get_next_line(0, &line);
//	return (line);
//}

//char	*read_line(void)
//{
//	char *line;
//
//	line = NULL;
//	get_next_line(0, &line);
//	return (line);
//}

/*
 * CHAR BY CHAR FUNCTIOIN
 */

int		is_read_ok(char ch, char **line, int *len)
{
	if (ch == '\n')
		return (0);
	if (ch != '\0')
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

	len = 0;
	if (!(line = ft_strdup("\0")))
		exit(1);
	while (1)
	{
		ch = '\0';
		ret = read(0, &ch, 1);
		if (ret == 0 && len == 0)
		{
			free(line);
			line = ft_strdup("exit");		// TODO: add error mgt
			break ;
		}
		if (is_read_ok(ch, &line, &len))
			continue ;
		else
			break ;
	}
	return (line);
}