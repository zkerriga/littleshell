/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_single_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 22:31:54 by matrus            #+#    #+#             */
/*   Updated: 2020/09/14 22:31:55 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdlib.h>

//
#include <stdio.h>

/*
**	Counts MINIMAL length of shell word. E.d. RAW shell word (no expand and
**	with meta chars).
*/

int		shell_raw_word_len(char *str)
{
	int		quote;
	int 	d_quote;
	int		len;

	quote = 0;
	d_quote = 0;
	len = 0;
	while (	*str &&
			((quote || d_quote) ||
			(!(*str == '\\' && *(str + 1) == ' ') ||
			*str != ' ')))
	{
		if (*str == '\'' && !d_quote)
			quote = !quote;
		if (*str == '\"' && !quote)
			d_quote = !d_quote;
		str++;
		len++;
	}
	return (len);
}

void	form_raw_word(char *to, char **from)
{
	int		quote;
	int 	d_quote;
	int		i_to;
	
	quote = 0;
	d_quote = 0;
	i_to = 0;
	(*from)--;
	while (	*(++(*from)) &&
			((quote || d_quote) ||
			((**from == ' ' && *(*from - 1) == '\\') ||
			**from != ' ')))
	{
		if (**from == '\'' && !d_quote)
		{
			quote = !quote;
			continue ;
		}
		if (**from == '\"' && !quote)
		{
			d_quote = !d_quote;
			continue ;
		}
		if (**from)
			to[i_to++] = **from;
	}
}

char	*get_shell_word_and_go_next(char **str)
{
	char	*word;
	int		w_len;

	w_len = shell_raw_word_len(*str);
	word = (char*)malloc(sizeof(char) * (w_len + 1));
	ft_bzero(word, sizeof(char) * (w_len + 1));
	form_raw_word(word, str);
	//expand_shell_word(&word);
	return (word);
}

char	**shell_word_split_with_env(char *str)
{
	char	**tab_word;
	int		i_word;

	tab_word = (char**)malloc(sizeof(char*));
	*tab_word = NULL;
	i_word = 0;
	while (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (*str)
		{
			tab_word[i_word] = get_shell_word_and_go_next(&str);	// TODO: mignt be malloc error
			i_word++;
			if (!(tab_word = (char **)ft_realloc_tab((void **)tab_word, i_word, i_word + 1)))
				printf("Malloc error in shell_word_split_with_env\n"); // TODO: error check
		}
	}
	return (tab_word);
}

void	parse_single_command(char *cmd_str, t_command *cmd)
{
	char	**tab_word;

	tab_word = shell_word_split_with_env(cmd_str);
	// TEST each cmd_str should separate on words properly
	printf("command: %s\n", cmd_str);
	while (*tab_word)
	{
		printf("word: %s\n", *tab_word);
		tab_word++;
	}
	printf("\n\n");
	// TEST END
	if (cmd)
	{
		;
	}
}

