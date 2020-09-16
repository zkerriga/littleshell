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
	while (*tab)
		*tab = *(tab + 1);
}

static char *has_arg_redir(char *arg, const char *redt)
{
	int		red_len;
	char	*red_word;

	red_word = arg;
	red_len = ft_strlen(redt);
	while (red_word && ft_isspace(*arg))
		red_word++;
	if (!ft_strncmp(red_word, redt, red_len))
	{
		red_word = ft_strdup(red_word + red_len);	// TODO: add error managment
		free(arg);
		return (red_word);
	}
	return (NULL);
}

char		**parse_redirection(char **args_tab, const char *redt)
{
	char	**redir_tab;
	int		tab_i;
	char	*redir_word;

	if (!(redir_tab = (char **)malloc(sizeof(*redir_tab))))
		exit(1); // TODO: add error managment;
	tab_i = 0;
	*redir_tab = NULL;
	redir_word = NULL;
	while (*args_tab)
	{
		if ((redir_word = has_arg_redir(*args_tab, redt)))
		{
			redir_tab = (char **)ft_realloc_tab((void **)redir_tab, tab_i + 1, tab_i + 2);
			redir_tab[tab_i++] = redir_word;
			redir_tab[tab_i] = NULL;
			tab_shift(args_tab);
		}
		else
			++args_tab;
	}
	return (redir_tab);
}