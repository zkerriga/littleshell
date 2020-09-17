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

static void	tab_shift(char **tab)
{
	*tab = *(tab + 1);
	while (tab++ && *tab)
		*tab = *(tab + 1);
}

char		**parse_redirection(char **args_tab, const char *redt)
{
	char	**redir_tab;
	int		tab_i;

	if (!(redir_tab = (char **)malloc(sizeof(*redir_tab))))
		exit(1); // TODO: add error managment;
	tab_i = 0;
	*redir_tab = NULL;
	while (*args_tab)
	{
		if (!ft_strncmp(*args_tab, redt, ft_strlen(redt)))
		{
			redir_tab = (char **)ft_realloc_tab((void **)redir_tab, tab_i + 1, tab_i + 2);
			free(*args_tab);
			tab_shift(args_tab);
			if (*args_tab)
			{
				redir_tab[tab_i++] = *args_tab;
				tab_shift(args_tab);
			}
			else
				redir_tab[tab_i++] = ft_strdup(""); // TODO: error check
			redir_tab[tab_i] = NULL;
		}
		else
			++args_tab;
	}
	return (redir_tab);
}

const char	*find_last_redir_out(char **args_tab)
{
	const char	*redir_last;

	redir_last = NULL;
	while (*args_tab)
	{
		if (!ft_strncmp(*args_tab, ">", 1) || !ft_strncmp(*args_tab, ">>", 1))
			redir_last = *(args_tab + 1);
		++args_tab;
	}
	return (redir_last);
}