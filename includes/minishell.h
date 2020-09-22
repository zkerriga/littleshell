/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:08:28 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/12 15:08:31 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

typedef struct	s_cmd
{
	char		*cmd_name;
	char		**args;
	char		**redir_in;
	char		**redir_in_app;
	char		**redir_out;
	char		**redir_out_app;
	const char	*redir_out_last;
	int			last_is_double;
	char		next_operator[2];
	int			is_empty;
}				t_command;

extern int		g_sigint;
extern int		g_isread;

#endif
