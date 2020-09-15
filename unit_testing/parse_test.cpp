#include "gtest/gtest.h"

extern "C" {
#include <stdio.h>
#include "minishell.h"
#include "environment.h"
#include "read_line.h"
#include "exec_all_commands.h"
#include "parse_commands.h"
};

char *parse_first_cmd_and_go_next(char *cmd_line, t_command *cmd, t_env *env)
{
	char	*cur_cmd_line;

	cur_cmd_line = cmd_line;
	while (*cmd_line && !does_command_separates(&cmd_line))
		cmd_line++;
	set_separator_type(&cmd_line, cmd);
	if (*cmd_line)
	{
		*cmd_line = '\0';
		cmd_line++;
	}
	// TEST		cmd_line should separate properly, operator type should set properly
	// printf("type after: %1c%1c ", cmd->next_operator[0], cmd->next_operator[1]);
	// printf("parsed cmd: %s\n", cur_cmd_line);
	// END TEST

	// parse_single_command(cur_cmd_line, cmd) is next task
//	parse_single_command(cur_cmd_line, cmd, env);
	return (cmd_line);
}

t_command	*new_command()
{
	t_command	*new_command;

	if (!(new_command = (t_command*)ft_calloc(1, sizeof(t_command))))
		return (NULL); // TODO: error check
	return (new_command);
}

TEST (parse, parse_1)
{
	const char	*envp[3] = {"HOME=/zkerriga/", "PATH=/zkerriga/21/school/", NULL};
	t_env		*env = environment_new(envp);
	char		*cmd_line = strdup("echo 1 | echo 2");
	t_command	*cur_cmd = new_command();

	cmd_line = parse_first_cmd_and_go_next(cmd_line, cur_cmd, env);
	ASSERT_STREQ(" echo 2", cmd_line);
}