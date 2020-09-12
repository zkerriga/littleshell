/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_command_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:54:46 by matrus            #+#    #+#             */
/*   Updated: 2020/09/12 15:54:48 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*clear_command_line(char *cmd_line)
{
	char *clear_cmd_line;

	clear_cmd_line = NULL;
	while (*cmd_line)
	{

		cmd_line++;
	}
	return (clear_cmd_line);
}

//						world =_hhe_'f'

// 		cmd: 			ehco \' hello $world ' hahah '
//		clean_str? :	echo ' hello _hhe_'f' ' hahah '
// 		echo:	 		ehco ' hello _hhe_'f'  hahah