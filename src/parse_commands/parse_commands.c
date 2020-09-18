/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 17:27:14 by matrus            #+#    #+#             */
/*   Updated: 2020/09/12 17:27:15 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include "parse_commands.h"
#include "environment.h"
#include "test_minishell.h"


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

/*
t_command	*new_command()
{
	t_command	*new_command;

	if (!(new_command = (t_command*)ft_calloc(1, sizeof(t_command))))
		return (NULL);
	return (new_command);
}
*/

/*
**	Parse command from *cmd_line till separate char (';' or '|'), then
**	shift *cmd_line to next command, then
**	write parsed information into *cmd, then
**	return modified *cmd_line;
*/

char	*parse_first_cmd_and_go_next(char *cmd_line,
										t_command *cmd, t_env *env)
{
	char	*cur_cmd_line;

	cur_cmd_line = cmd_line;
	while (*cmd_line && !does_command_separates(&cmd_line))
		cmd_line++;
	set_separator_type(&cmd_line, cmd);
	if (*cmd_line)
	{
		*cmd_line = '\0';
		cmd_line++;
	}
	parse_single_command(cur_cmd_line, cmd, env);
	return (cmd_line);
}

/*
**	OLD FUNCTION! NOT USED NOW!

t_list *parse_command_line(char *cmd_line, t_env *env)
{
	t_list		*lst_head;
	t_list		*lst_cur;
	t_command	*cur_cmd;

	lst_cur = NULL;
	lst_head = NULL;
	while (*cmd_line)
	{
		if (!(cur_cmd = new_command()) ||
			!(lst_cur = ft_lstnew(cur_cmd)))
			ft_putendl_fd("Malloc error parse commands!", 1);
		cmd_line = parse_first_cmd_and_go_next(cmd_line, lst_cur->content, env);
		if (((t_command*)(lst_cur->content))->is_empty)
		{
			free(lst_cur->content);
			free(lst_cur);
		}
		else
		{
			ft_lstadd_back(&lst_head, lst_cur);
			//test_cmd_print(lst_cur->content);
		}
	}
	return (lst_head);
}
*/
