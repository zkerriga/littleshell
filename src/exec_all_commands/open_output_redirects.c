/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_output_redirects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 08:09:47 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/18 08:09:53 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include "builtin_functions.h"

/*
** The function creates a file by opening and closing it, and detects errors.
*/

static int	open_mask(char *filename, int flags)
{
	const int	redirect_error_code = 1;
	int			fd;

	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		write_err(filename, NULL, strerror(errno));
		return (redirect_error_code);
	}
	close(fd);
	return (0);
}

/*
** The function simply creates all files that were marked with exit redirects.
** If an error occurs, it returns a non-zero status that must complete
** the execution of this command.
*/

int			open_output_redirects(t_command *cmd)
{
	int			status;
	char		**filename_tab;

	status = 0;
	if ((filename_tab = cmd->redir_out))
	{
		while (*filename_tab)
		{
			if ((status = open_mask(*filename_tab, O_CREAT | O_WRONLY)))
				return (status);
			++filename_tab;
		}
	}
	if ((filename_tab = cmd->redir_out_app))
	{
		while (*filename_tab)
		{
			if ((status = open_mask(*filename_tab, O_CREAT | O_WRONLY | O_APPEND)))
				return (status);
			++filename_tab;
		}
	}
	return (status);
}
