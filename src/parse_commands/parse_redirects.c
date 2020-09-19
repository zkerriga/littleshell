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
#include "error_manager.h"

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
		errman(ENOMEM, NULL);
	tab_i = 0;
	*redir_tab = NULL;
	while (*args_tab)
	{
		if (!ft_strncmp(*args_tab, redt, ft_strlen(redt)))
		{
			if (!(redir_tab = (char **)ft_realloc_tab((void **)redir_tab, tab_i + 1, tab_i + 2))) //TODO:malloc
				errman(ENOMEM, NULL);
			free(*args_tab);
			tab_shift(args_tab);
			if (*args_tab)
			{
				redir_tab[tab_i++] = *args_tab;
				tab_shift(args_tab);
			}
			else if (!(redir_tab[tab_i++] = ft_strdup("")))
				errman(ENOMEM, NULL);
			redir_tab[tab_i] = NULL;
		}
		else
			++args_tab;
	}
	return (redir_tab);
}

void	set_last_output_redirect_info(char **args_tab, t_command *cmd)
{
	cmd->redir_out_last = NULL;
	cmd->last_is_double = -1;
	while (*args_tab)
	{
		if (!ft_strncmp(*args_tab, ">>", 2))
		{
			cmd->redir_out_last = args_tab[1];
			cmd->last_is_double = 1;
		}
		else if (!ft_strncmp(*args_tab, ">", 1))
		{
			cmd->redir_out_last = args_tab[1];
			cmd->last_is_double = 0;
		}
		++args_tab;
	}
}
