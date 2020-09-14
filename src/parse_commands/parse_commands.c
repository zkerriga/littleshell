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

//
#include <stdio.h>

t_command	*destroy_command(t_command *cmd)
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
	cmd = NULL;
	return (NULL);
}

t_command	*new_command()
{
	t_command	*new_command;

	if (!(new_command = (t_command*)malloc(sizeof(t_command))))
		return (NULL);
	if (!(new_command->args = (char**)malloc(sizeof(char*))))
		return (destroy_command(new_command));		// Ok that destroy() returns smth??
	*new_command->args = NULL;
	if (!(new_command->cmd_name = (char*)malloc(sizeof(char))))
		return (destroy_command(new_command));
	*new_command->cmd_name = '\0';
	if (!(new_command->redir_in = (char**)malloc(sizeof(char*))))
		return (destroy_command(new_command));
	*new_command->redir_in = NULL;
	if (!(new_command->redir_out = (char**)malloc(sizeof(char*))))
		return (destroy_command(new_command));
	*new_command->redir_out = NULL;
	if (!(new_command->redir_in_app = (char**)malloc(sizeof(char*))))
		return (destroy_command(new_command));
	*new_command->redir_in_app = NULL;
	if (!(new_command->redir_out_app = (char**)malloc(sizeof(char*))))
		return (destroy_command(new_command));
	*new_command->redir_out_app = NULL;
	new_command->cmd_name[0] = '\0';
	new_command->cmd_name[1] = '\0';
	return (new_command);
}

int		is_command_separator(const char *line)
{
	if (line[0] == '|')
		return (1);
	if (line[0] == ';')
		return (1);
	return (0);
}

/*
**	Retruns 1 if command separator found in *cmd_line given quotation marks;
**	If '\' occurs, function moves ptr of *cmd_line skipping that backslash.
**	Returns 0 otherwise.
*/

int		does_command_separates(char **cmd_line)
{
	static int	was_quote;
	static int	was_d_quote;

	if ((!(was_quote || was_d_quote) &&
		is_command_separator(*cmd_line)) ||
		(**cmd_line == '\\' && *(*cmd_line + 1) == '\0'))	// case with last backslash
		return (1);
	if (**cmd_line == '\\')
	{
		(*cmd_line)++;
		return (0);
	}
	if (**cmd_line == '\'' && !was_d_quote)
		was_quote = !was_quote;
	if (**cmd_line == '\"' && !was_quote)
		was_d_quote = !was_d_quote;
	return (0);
}

/*
**	sets cmd->next_operator;
**	if separator contains 2 chars, shifts ptr *cmd_line by 1
*/

void	set_separator_type(char **cmd_line, t_command *cmd)
{
	cmd->next_operator[0] = '\0';
	cmd->next_operator[1] = '\0';
	if (**cmd_line == '\\')
		;
	else if (**cmd_line == ';')
		cmd->next_operator[0] = ';';
	else if (**cmd_line == '|')
		cmd->next_operator[0] = '|';
	else
		return ;
}

/*
**	Parse command from *cmd_line till separate char (';' or '|'), then
**	write information into *cmd, then
**	shift *cmd_line to next command, then
**	return modified *cmd_line;
*/

char	*parse_first_cmd_and_go_next(char *cmd_line, t_command *cmd)
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
	printf("type after: %1c%1c ", cmd->next_operator[0], cmd->next_operator[1]);
	printf("parsed cmd: %s\n", cur_cmd_line);
	//parse_single_command(cur_cmd_line, cmd);
	return (cmd_line);
}

t_list	*parse_command_line(char *cmd_line)
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
			printf("Malloc error parse commands!\n");	//	TODO: add error management
		cmd_line = parse_first_cmd_and_go_next(cmd_line, lst_cur->content);

		//ft_lstadd_back(&lst_head, lst_cur);
	}
	return (lst_head);
}