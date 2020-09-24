/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 17:24:05 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/12 17:24:06 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_COMMANDS_H
# define PARSE_COMMANDS_H

# include "libft.h"
# include "environment.h"

char		*parse_first_cmd_and_go_next(char *cmd_line,
											t_command *cmd, t_env *env);

void		destroy_command(t_command *cmd);

int does_command_separates(char **cmd_line, int *was_quote, int *was_d_quote);
void		set_separator_type(char **cmd_line, t_command *cmd);

char		**shell_word_split_with_env(char *str, t_env *env);
void		parse_single_command(char *cmd_str, t_command *cmd, t_env *env);

char		**parse_redirection(char **args_tab, const char *redt);
int			is_valid_command(char *cmd_line, int sep_exist, char *is_sep);
void		set_last_output_redirect_info(char **args_tab, t_command *cmd);

#endif
