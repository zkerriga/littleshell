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

static int	write_syntax_error(char trouble1, char trouble2)
{
	char		trouble_str[3];
	const char	*description = "syntax error near unexpected token";

	trouble_str[0] = trouble1;
	trouble_str[1] = trouble2;
	trouble_str[2] = '\0';
	write(2, "minishell: ", 11);
	write(2, description, ft_strlen(description));
	write(2, " `", 2);
	write(2, trouble_str, ft_strlen(trouble_str));
	write(2, "'\n", 2);
	return (0);
}

static char	*move_line_to_next_quot(char *line, char quote)
{
	++line;
	while (*line)
	{
		if (*line == '\\' && (line[1] == '"' || line[1] == '\''))
			++line;
		else if (*line == quote)
			break ;
		++line;
	}
	return (line);
}

int			is_valid_command(char *line, int sep_exist, char *is_sep)
{
	while (*line)
	{
		if (*line == '\\' && (line[1] == '"' || line[1] == '\''))
			++line;
		else if (*line == '"' || *line == '\'')
		{
			sep_exist = 0;
			line = move_line_to_next_quot(line, *line);
		}
		else if (!(is_sep = ft_strchr("&|;", *line)) && !ft_isspace(*line))
			sep_exist = 0;
		else if (is_sep && !sep_exist)
		{
			sep_exist = 1;
			if (*line == line[1] && *line == ';')
				return (write_syntax_error(';', ';'));
			else if (*line == line[1])
				++line;
		}
		else if (is_sep)
			return (write_syntax_error(*line, (line[1] == *line) ? *line : 0));
		++line;
	}
	return (1);
}
