/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_comand_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:54:46 by matrus            #+#    #+#             */
/*   Updated: 2020/09/12 15:54:48 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *clear_comand_line(char *cmd_line)
{
//	char *clear_cmd_line;

	while (*cmd_line)
	{

		cmd_line++;
	}
}

//						world =_hhe_'f'

// 		cmd: 			ehco \' hello $world ' hahah '
//		clean_str? :	echo ' hello _hhe_'f' ' hahah '
// 		echo:	 		ehco ' hello _hhe_'f'  hahah