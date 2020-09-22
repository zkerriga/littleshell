/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zkerriga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 14:58:02 by zkerriga          #+#    #+#             */
/*   Updated: 2020/09/12 14:58:06 by zkerriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "read_line.h"
#include "exec_all_commands.h"
#include "parse_commands.h"
#include "environment.h"
#include "signal_handlers.h"
#include "error_manager.h"

int		g_sigint;
int		g_isread;

int		execute_line(char *cmd_line, t_env *env)
{
	t_command	cmd;
	int			status;

	status = 0;
	ft_bzero(&cmd, sizeof(cmd));
	while (*cmd_line)
	{
		cmd_line = parse_first_cmd_and_go_next(cmd_line, &cmd, env);
		if (!cmd.is_empty)
			status = exec_one_command(&cmd, env);
		env->set_status(env, status);
		destroy_command(&cmd);
		if (g_sigint)
			break ;
	}
	return (status);
}

void	loop(t_env *env)
{
	char	*cmd_line;
	char	*current_path;

	write(1, "\033c", ft_strlen("\033c"));
	while (1)
	{
		cmd_line = NULL;
		current_path = getcwd(NULL, 0);
		if (!g_sigint)
		{
			write(1, current_path, ft_strlen(current_path));
			write(1, ": ", 2);
		}
		cmd_line = read_line(env);
		g_sigint = 0;
		if (is_valid_command(cmd_line, 1, NULL))
			execute_line(cmd_line, env);
		free(cmd_line);
		free(current_path);
		if (errno == ENOMEM)
			break ;
	}
}

int		main(int ac, char **av, char **envp)
{
	t_env	*env;

	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, sigint_handler);
	if (!(env = environment_new((const char **)envp)))
		errman(ENOMEM, NULL);
	if (ac && av)
	{
		loop(env);
	}
	env->del(env);
	return (0);
}
