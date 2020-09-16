/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cmd_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 09:55:55 by matrus            #+#    #+#             */
/*   Updated: 2020/09/16 09:55:57 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_minishell.h"

void	test_cmd_print(t_command *cmd)
{
	char	**tab_i;

	ft_putendl_fd("\nCommand name: ", 1);
	ft_putendl_fd(cmd->cmd_name, 1);
	ft_putendl_fd("Command arguments:", 1);
	tab_i = cmd->args;
	while (tab_i && *tab_i)
	{
		ft_putstr_fd(*tab_i, 1);
		ft_putstr_fd(*(++tab_i) ? ", " : ".", 1);
	}
	ft_putstr_fd("\n", 1);

	ft_putendl_fd("Redirects IN '<':", 1);
	tab_i = cmd->redir_in;
	while (tab_i && *tab_i)
	{
		ft_putstr_fd(*tab_i, 1);
		ft_putstr_fd(*(++tab_i) ? ", " : ".", 1);
	}
	ft_putstr_fd("\n", 1);

	ft_putendl_fd("Redirects OUT '>':", 1);
	tab_i = cmd->redir_out;
	while (tab_i && *tab_i)
	{
		ft_putstr_fd(*tab_i, 1);
		ft_putstr_fd(*(++tab_i) ? ", " : ".", 1);
	}
	ft_putstr_fd("\n", 1);

	ft_putendl_fd("Redirects IN APPEND '<<':", 1);
	tab_i = cmd->redir_in_app;
	while (tab_i && *tab_i)
	{
		ft_putstr_fd(*tab_i, 1);
		ft_putstr_fd(*(++tab_i) ? ", " : ".", 1);
	}
	ft_putstr_fd("\n", 1);

	ft_putendl_fd("Redirects OUT APPEND '>>'", 1);
	tab_i = cmd->redir_out_app;
	while (tab_i && *tab_i)
	{
		ft_putstr_fd(*tab_i, 1);
		ft_putstr_fd(*(++tab_i) ? ", " : ".", 1);
	}
	ft_putstr_fd("\n", 1);

	ft_putstr_fd("Separator: ", 1);
	ft_putchar_fd(cmd->next_operator[0], 1);
	ft_putchar_fd(cmd->next_operator[1], 1);
	ft_putendl_fd("", 1);
}

