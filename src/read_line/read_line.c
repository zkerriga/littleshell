/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:32:04 by matrus            #+#    #+#             */
/*   Updated: 2020/09/12 15:32:14 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include "minishell.h"
#include "error_manager.h"
#include "environment.h"
#include "read_line.h"

static int	is_read_ok(char ch, char **line, int *len)
{
	if (ch == '\n')
		return (0);
	if (ft_isprint(ch) || ft_isspace(ch))
	{
		if (!(*line = ft_realloc(*line, (*len) + 2, (*len) + 1)))
			errman(ENOMEM, NULL);
		(*line)[(*len)++] = ch;
		(*line)[*len] = '\0';
	}
	return (1);
}

static void	clear_metachar_d(void)
{
	write(1, "  \b\b", 4);
}

static void	read_init(t_local *l)
{
	l->len = 0;
	g_isread = 1;
	if (!(l->line = ft_strdup("\0")))
		errman(ENOMEM, NULL);
}

char		*read_line(t_env *env)
{
	t_local	l;

	read_init(&l);
	while (1)
	{
		l.ch = '\0';
		l.save_sigint_value = g_sigint;
		l.ret = read(0, &l.ch, 1);
		if (g_sigint != l.save_sigint_value)
			env->set_status(env, 1);
		if (l.ret == 0 && l.len == 0)
		{
			free(l.line);
			if (!(l.line = ft_strdup("exit")))
				errman(ENOMEM, NULL);
			break ;
		}
		if (l.ret == 0)
			clear_metachar_d();
		if (!is_read_ok(l.ch, &l.line, &l.len))
			break ;
	}
	g_isread = 0;
	return (l.line);
}
