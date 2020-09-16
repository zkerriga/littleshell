/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 08:21:58 by matrus            #+#    #+#             */
/*   Updated: 2020/09/16 08:21:59 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_commands.h"

char	**parse_redirection(char ***args_tab, const char *redt)
{
	char	**redir_tab;
	char	**cur_tab;
	int		redir_tab_i;

	cur_tab = *args_tab;
	if (!(redir_tab = (char **)malloc(sizeof(*redir_tab))))
		exit(1); // TODO: add error managment;
	redir_tab_i = 0;
	*redir_tab = NULL;

	// Go for each arg in args and try parse redir.
	while (cur_tab)
	{
		if (has_arg_redir(*cur_tab, redt))
		{
			ft_realloc_tab(redir_tab, redir_tab_i + 1, redir_tab_i + 2);
			redir_tab[redir_tab_i++] = *cur_tab;
			tab_shift()
		}

		++cur_tab;
	}
	return (redir_tab);
}