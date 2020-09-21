/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stop_status.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 17:30:19 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/19 17:30:20 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_all_commands.h"

int		parse_stop_status(int stat)
{
	const char	*output_str = "Quit:\t";
	int			sig;

	if (WIFSIGNALED(stat))
	{
		sig = WTERMSIG(stat);
		if (sig == SIGQUIT)
		{
			write(2, output_str, ft_strlen(output_str));
			ft_putnbr_fd(WTERMSIG(stat), 2);
			write(2, "\n", 1);
		}
		return (128 + sig);
	}
	return (WEXITSTATUS(stat));
}
