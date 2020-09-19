/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 09:53:29 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/19 09:53:30 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_command(t_command *cmd)
{
	if (cmd->redir_out_app)
		ft_free_tab((void **)cmd->redir_out_app);
	if (cmd->redir_out)
		ft_free_tab((void **)cmd->redir_out);
	if (cmd->redir_in)
		ft_free_tab((void **)cmd->redir_in);
	if (cmd->redir_in_app)
		ft_free_tab((void **)cmd->redir_in_app);
	if (cmd->args)
		ft_free_tab((void **)cmd->args);
	if (cmd->cmd_name)
		free(cmd->cmd_name);
	ft_bzero(cmd, sizeof(*cmd));
}
