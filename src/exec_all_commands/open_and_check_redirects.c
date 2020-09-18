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

static int	open_mask(char *filename, int flags, unsigned int permissions)
{
	const int	redirect_error_code = 1;
	int			fd;

	if (permissions)
		fd = open(filename, flags, permissions);
	else
		fd = open(filename, flags);
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
			if ((status = open_mask(*filename_tab, O_CREAT | O_WRONLY, 0644)))
				return (status);
			++filename_tab;
		}
	}
	if ((filename_tab = cmd->redir_out_app))
	{
		while (*filename_tab)
		{
			if ((status = open_mask(*filename_tab, O_CREAT | O_WRONLY | O_APPEND, 0644)))
				return (status);
			++filename_tab;
		}
	}
	return (status);
}

/*
** The function tries to open all files in order to check their status.
** If an error occurs, the command terminates with a non-zero status.
*/

int	check_input_redirects(t_command *cmd)
{
	int			status;
	char		**filename_tab;

	status = 0;
	if ((filename_tab = cmd->redir_in))
	{
		while (*filename_tab)
		{
			if ((status = open_mask(*filename_tab, O_RDONLY, 0)))
				return (status);
			++filename_tab;
		}
	}
	if ((filename_tab = cmd->redir_in_app))
	{
		while (*filename_tab)
		{
			if ((status = open_mask(*filename_tab, O_RDONLY, 0)))
				return (status);
			++filename_tab;
		}
	}
	return (status);
}
