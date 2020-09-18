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

/*
**	Just return line from user.
**	No error management
*/

char	*read_line(void)
{
	char *line;

	line = NULL;
	get_next_line(0, &line);
	return (line);
}

/*
 * CHAR BY CHAR FUNCTIOIN
 */

//char	*read_line(void)
//{
//	char	*line;
//	int 	len;
//	char	ch;
//
//	len = 0;
//	if (!(line = ft_strdup("\0")))
//		exit(1);
//	while (1)
//	{
//		read(0, &ch, 1);
//		if (ch == '\n')
//			break ;
//		else if (ch == EOF)
//			continue ;
//		else
//		{
//			if (!(line = ft_realloc(line, len + 1, len + 2))) // TODO: add err management
//				exit(1);
//			line[len++] = ch;
//			line[len] = '\0';
//		}
//	}
//
//	return (line);
//}