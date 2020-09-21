/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 17:46:32 by matrus            #+#    #+#             */
/*   Updated: 2020/09/18 17:46:33 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "read_line.h"

static void	clear_metachar_sigintquit()
{
	write(1, "\b\b  \b\b", 6);
}

void	sigint_handler(void)
{
	char *current_path;

	if (g_isread)
		clear_metachar_sigintquit();
	g_sigint = 1;
	current_path = getcwd(NULL, 0);
	write(1, "\n", 1);
	write(1, current_path, ft_strlen(current_path));
	write(1, ": ", 2);
	free(current_path);
}

void	sigquit_handler(void)
{
	if (g_isread)
		clear_metachar_sigintquit();
}
