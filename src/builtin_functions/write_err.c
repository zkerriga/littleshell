/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 13:21:34 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/16 13:21:35 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The function generates and prints an error string in stderr.
** If the second argument is NULL, the command argument will not participate
** in the error output.
*/

void	write_err(char *cmd_name, char *trouble_str, char *description)
{
	write(2, "minishell: ", 11);
	if (cmd_name)
	{
		write(2, cmd_name, ft_strlen(cmd_name));
		write(2, ": ", 3);
	}
	if (trouble_str)
	{
		write(2, "`", 1);
		write(2, trouble_str, ft_strlen(trouble_str));
		write(2, "': ", 3);
	}
	write(2, description, ft_strlen(description));
	write(2, "\n", 1);
}
