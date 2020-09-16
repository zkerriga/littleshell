//
// Created by Mushroom Atrus on 9/15/20.
//

#include "gtest/gtest.h"

extern "C" {
#include <stdio.h>
#include "minishell.h"
#include "environment.h"
#include "read_line.h"
#include "exec_all_commands.h"
#include "parse_commands.h"
};

TEST(env, env_get_set_status) {
	const char *envp[10] = {"HOME=/zkerriga/", "PATH=/zkerriga/21/school/",
							"D==1=2=3=4=5=6=7=8=9=", "E=",
							"F====================", NULL};
	t_env *env;

	env = environment_new(envp);
	ASSERT_EQ(0, env->get_status(env));
	env->set_status(env, 1234);
	ASSERT_EQ(1234, env->get_status(env));
	env->set_status(env, -999999);
	ASSERT_EQ(-999999, env->get_status(env));
}

TEST(env, env_get_value)
{
	const char	*envp[10] = {"HOME=/zkerriga/", "PATH=/zkerriga/21/school/",
						 "D==1=2=3=4=5=6=7=8=9=", "E=", "F====================", NULL};
	t_env *env;

	env = environment_new(envp);

	ASSERT_STREQ("/zkerriga/", env->get_value(env, "HOME"));
	ASSERT_STREQ("=1=2=3=4=5=6=7=8=9=", env->get_value(env, "D"));
	ASSERT_STREQ("", env->get_value(env, "E"));
	ASSERT_STREQ("===================", env->get_value(env, "F"));
	ASSERT_EQ(nullptr, env->get_value(env, "F"));
}

TEST(env, env_add)
{
	const char	*envp[10] = {"HOME=/zkerriga/", "PATH=/zkerriga/21/school/",
						 "D==1=2=3=4=5=6=7=8=9=", "E=", "F====================", NULL};
	t_env *env;

	env = environment_new(envp);


	ASSERT_STREQ("/zkerriga/", env->get_value(env, "HOME"));
	ASSERT_STREQ("=1=2=3=4=5=6=7=8=9=", env->get_value(env, "D"));
	ASSERT_STREQ("", env->get_value(env, "E"));
	ASSERT_STREQ("===================", env->get_value(env, "F"));
	ASSERT_EQ(nullptr, env->get_value(env, "G"));

	env->add(env, "G", "=====");
	env->add(env, "H", "");
	env->add(env, "I", "kekek\"  |||||  \\$");
	env->add(env, "K", "   ''&;''   ");
	ASSERT_STREQ("=====", env->get_value(env, "G"));
	ASSERT_STREQ("", env->get_value(env, "H"));
	ASSERT_STREQ("kekek\"  |||||  \\$", env->get_value(env, "I"));
	ASSERT_STREQ("   ''&;''   ", env->get_value(env, "K"));

	env->add(env, "G", "-----");
	env->add(env, "H", "MUSH");
	env->add(env, "I", "\\");
	env->add(env, "K", "\0");
	ASSERT_STREQ("-----", env->get_value(env, "G"));
	ASSERT_STREQ("MUSH", env->get_value(env, "H"));
	ASSERT_STREQ("\\", env->get_value(env, "I"));
	ASSERT_STREQ("\0", env->get_value(env, "K"));
}

TEST(env, env_remove)
{
	const char	*envp[10] = {"HOME=/zkerriga/", "PATH=/zkerriga/21/school/",
							   "D==1=2=3=4=5=6=7=8=9=", "E=", "F====================", NULL};
	t_env *env;

	env = environment_new(envp);


	ASSERT_STREQ("/zkerriga/", env->get_value(env, "HOME"));
	ASSERT_STREQ("=1=2=3=4=5=6=7=8=9=", env->get_value(env, "D"));
	ASSERT_STREQ("", env->get_value(env, "E"));
	ASSERT_STREQ("===================", env->get_value(env, "F"));
	ASSERT_EQ(nullptr, env->get_value(env, "G"));

	env->add(env, "G", "=====");
	env->add(env, "H", "");
	env->add(env, "I", "kekek\"  |||||  \\$");
	env->add(env, "K", "   ''&;''   ");
	ASSERT_STREQ("=====", env->get_value(env, "G"));
	ASSERT_STREQ("", env->get_value(env, "H"));
	ASSERT_STREQ("kekek\"  |||||  \\$", env->get_value(env, "I"));
	ASSERT_STREQ("   ''&;''   ", env->get_value(env, "K"));

	env->add(env, "G", "-----");
	env->add(env, "H", "MUSH");
	env->add(env, "I", "\\");
	env->add(env, "K", "\0");
	ASSERT_STREQ("-----", env->get_value(env, "G"));
	ASSERT_STREQ("MUSH", env->get_value(env, "H"));
	ASSERT_STREQ("\\", env->get_value(env, "I"));
	ASSERT_STREQ("\0", env->get_value(env, "K"));

	env->remove(env, "PATH");
	env->remove(env, "D");
	env->remove(env, "E");
	env->remove(env, "F");
	env->remove(env, "G");
	env->remove(env, "H");
	env->remove(env, "I");
	env->remove(env, "K");
	env->remove(env, "F");
	env->remove(env, "HOME");
	ASSERT_EQ(nullptr, env->get_value(env, "PATH"));
	ASSERT_EQ(nullptr, env->get_value(env, "D"));
	ASSERT_EQ(nullptr, env->get_value(env, "E"));
	ASSERT_EQ(nullptr, env->get_value(env, "F"));
	ASSERT_EQ(nullptr, env->get_value(env, "G"));
	ASSERT_EQ(nullptr, env->get_value(env, "H"));
	ASSERT_EQ(nullptr, env->get_value(env, "I"));
	ASSERT_EQ(nullptr, env->get_value(env, "K"));
	ASSERT_EQ(nullptr, env->get_value(env, "F"));
	ASSERT_EQ(nullptr, env->get_value(env, "HOME"));
}

TEST(env, env_print)
{
	const char	*envp[10] = {"HOME=/zkerriga/", "PATH=/zkerriga/21/school/",
							   "D==1=2=3=4=5=6=7=8=9=", "E=", "F====================", NULL};
	t_env *env;

	env = environment_new(envp);


	ASSERT_STREQ("/zkerriga/", env->get_value(env, "HOME"));
	ASSERT_STREQ("=1=2=3=4=5=6=7=8=9=", env->get_value(env, "D"));
	ASSERT_STREQ("", env->get_value(env, "E"));
	ASSERT_STREQ("===================", env->get_value(env, "F"));
	ASSERT_EQ(nullptr, env->get_value(env, "G"));

	env->add(env, "G", "=====");
	env->add(env, "H", "");
	env->add(env, "I", "kekek\"  |||||  \\$");
	env->add(env, "K", "   ''&;''   ");
	ASSERT_STREQ("=====", env->get_value(env, "G"));
	ASSERT_STREQ("", env->get_value(env, "H"));
	ASSERT_STREQ("kekek\"  |||||  \\$", env->get_value(env, "I"));
	ASSERT_STREQ("   ''&;''   ", env->get_value(env, "K"));

	env->add(env, "G", "-----");
	env->add(env, "H", "MUSH");
	env->add(env, "I", "\\");
	env->add(env, "K", "\0");
	ASSERT_STREQ("-----", env->get_value(env, "G"));
	ASSERT_STREQ("MUSH", env->get_value(env, "H"));
	ASSERT_STREQ("\\", env->get_value(env, "I"));
	ASSERT_STREQ("\0", env->get_value(env, "K"));

	env->print(env, 1);

	env->remove(env, "PATH");
	env->remove(env, "D");
	env->remove(env, "E");
	env->remove(env, "F");
	env->remove(env, "G");
	env->remove(env, "H");
	env->remove(env, "I");
	env->remove(env, "K");
	env->remove(env, "F");
	env->remove(env, "HOME");
	ASSERT_EQ(nullptr, env->get_value(env, "PATH"));
	ASSERT_EQ(nullptr, env->get_value(env, "D"));
	ASSERT_EQ(nullptr, env->get_value(env, "E"));
	ASSERT_EQ(nullptr, env->get_value(env, "F"));
	ASSERT_EQ(nullptr, env->get_value(env, "G"));
	ASSERT_EQ(nullptr, env->get_value(env, "H"));
	ASSERT_EQ(nullptr, env->get_value(env, "I"));
	ASSERT_EQ(nullptr, env->get_value(env, "K"));
	ASSERT_EQ(nullptr, env->get_value(env, "F"));
	ASSERT_EQ(nullptr, env->get_value(env, "HOME"));

	env->print(env, 1);
}
