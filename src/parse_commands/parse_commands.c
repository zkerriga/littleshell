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

//
#include <stdio.h>

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
	free(cmd);
}

t_command	*new_command()
{
	t_command	*new_command;

	if (!(new_command = (t_command*)ft_calloc(1, sizeof(t_command))))
		return (NULL); // TODO: error check
	return (new_command);
}

/*
**	Parse command from *cmd_line till separate char (';' or '|'), then
**	shift *cmd_line to next command, then
**	write parsed information into *cmd, then
**	return modified *cmd_line;
*/

char *parse_first_cmd_and_go_next(char *cmd_line, t_command *cmd, t_env *env)
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
	// TEST		cmd_line should separate properly, operator type should set properly
	// printf("type after: %1c%1c ", cmd->next_operator[0], cmd->next_operator[1]);
	// printf("parsed cmd: %s\n", cur_cmd_line);
	// END TEST

	// parse_single_command(cur_cmd_line, cmd) is next task
	parse_single_command(cur_cmd_line, cmd, env);
	return (cmd_line);
}

t_list *parse_command_line(char *cmd_line, t_env *env)
{
	t_list		*lst_head;
	t_list		*lst_cur;
	t_command	*cur_cmd;

	lst_cur = NULL;
	lst_head = NULL;
	while (*cmd_line)
	{
		if (!(cur_cmd = new_command()) ||		// TODO: refactor command_new
			!(lst_cur = ft_lstnew(cur_cmd)))
			printf("Malloc error parse commands!\n");	//	TODO: add error management
		cmd_line = parse_first_cmd_and_go_next(cmd_line, lst_cur->content, env);
		// yeah, there leaks cos no push in lst;
		//ft_lstadd_back(&lst_head, lst_cur);
	}
	return (lst_head);
}
