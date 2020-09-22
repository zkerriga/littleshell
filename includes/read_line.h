/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 17:24:11 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/12 17:24:12 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_LINE_H
# define READ_LINE_H

# include "environment.h"

typedef struct	s_local
{
	char		*line;
	int			len;
	int			ret;
	char		ch;
	int			save_sigint_value;
}				t_local;

char			*read_line(t_env *env);

#endif
