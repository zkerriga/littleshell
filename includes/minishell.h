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
}				t_cmd;

#endif
