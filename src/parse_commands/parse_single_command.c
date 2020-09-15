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
#include <environment.h>

/*
**	Counts MINIMAL length of shell word. E.d. RAW shell word (no expand and
**	with meta chars).
*/


// Probably not needed
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
// Probably not needed
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

#define SHELL_WORD_LEN 256

char *get_shell_word_and_go_next(char **str, t_env *env)
{
	char	*word;
	char 	*substr_to_copy;
	int		len_to_copy;
	int		w_len;
	int		i_word;
	int		quote;
	int 	d_quote;

	w_len = SHELL_WORD_LEN;
	word = (char*)ft_calloc(w_len, sizeof(*word));

	i_word = 0;
	while (**str && !ft_isspace(**str))
	{
		len_to_copy = 1;
		// Check quotes
		shell_word_check_quotes(str, &quote, &d_quote);

		if (!quote)
		{
			// Check backslash
			shell_word_check_backslash(str, d_quote);

			// Check expand
			shell_word_check_expand(str, &substr_to_copy, &len_to_copy);
		}
		// Check realloc
		shell_word_check_realloc(&word, len_to_copy);

		// Copy to arg
		ft_strlcpy(&(word[i_word++]), substr_to_copy, len_to_copy);

		++(*str);
	}


	env->get_value(env, "key");
	form_raw_word(word, str);
	//expand_shell_word(&word);
	return (word);
}

char **shell_word_split_with_env(char *str, t_env *env)
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
			tab_word[i_word] = get_shell_word_and_go_next(&str, env);	// TODO: mignt be malloc error
			i_word++;
			if (!(tab_word = (char **)ft_realloc_tab((void **)tab_word, i_word, i_word + 1)))
				printf("Malloc error in shell_word_split_with_env\n"); // TODO: error check
		}
	}
	return (tab_word);
}

void parse_single_command(char *cmd_str, t_command *cmd, t_env *env)
{
	char	**tab_word;
	char	**i_tab_word;

	tab_word = shell_word_split_with_env(cmd_str, env);
	i_tab_word = tab_word;

	// TEST each cmd_str should separate on words properly
	printf("command: %s\n", cmd_str);
	while (*tab_word)
	{
		printf("word: %s\n", *tab_word);
		tab_word++;
	}
	printf("\n\n");
	// TEST END

	while (*i_tab_word)
	{

		i_tab_word++;
	}

	if (cmd)
	{
		;
	}
}

