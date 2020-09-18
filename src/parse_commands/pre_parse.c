/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 18:12:15 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/17 18:12:17 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	write_syntax_error(char *trouble_str, char *description)
{
	write(2, "minishell: ", 11);
	write(2, description, ft_strlen(description));
	write(2, " `", 2);
	write(2, trouble_str, ft_strlen(trouble_str));
	write(2, "'\n", 2);
}

static char	*move_line_to_next_quot(char *line, char quote)
{
	++line;
	while (*line && *line != quote)
		++line;
	return (line);
}

int			is_valid_command(char *line)
{
	char	buf[3];
	int		active_separator_exist;
	char	*is_sep;

	ft_bzero(buf, 3);
	active_separator_exist = 0;
	while (*line)
	{
		if (*line == '"' || *line == '\'')
		{
			active_separator_exist = 0;
			line = move_line_to_next_quot(line, *line);
		}
		else if (!(is_sep = ft_strchr("&|;", *line)) && !ft_isspace(*line))
		{
			active_separator_exist = 0;
		}
		else if (is_sep && !active_separator_exist)
		{
			active_separator_exist = 1;
			if (*line == line[1] && *line == ';')
			{
				write_syntax_error(";;", "syntax error near unexpected token");
				return (0);
			}
			else if (*line == line[1])
				++line;
		}
		else if (is_sep && active_separator_exist)
		{
			buf[0] = *line;
			buf[1] = line[1] == *line ? *line : '\0';
			write_syntax_error(buf, "syntax error near unexpected token");
			return (0);
		}
		++line;
	}
	return (1);
}
