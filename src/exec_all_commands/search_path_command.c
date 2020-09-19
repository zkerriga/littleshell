/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 16:18:01 by matrus            #+#    #+#             */
/*   Updated: 2020/09/16 16:18:02 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include <sys/stat.h>
#include <dirent.h>
#include "error_manager.h"

static int	does_dir_contains_cmd(const char *path, const char *name)
{
	DIR				*dirp;
	struct dirent	*dp;
	size_t			len;

	dirp = opendir(path);
	if (dirp == NULL)
		return (0);
	len = ft_strlen(name);
	while ((dp = readdir(dirp)) != NULL)
	{
		if (dp->d_namlen == len && ft_strncmp(dp->d_name, name, len) == 0)
		{
			(void)closedir(dirp);
			return (1);
		}
	}
	(void)closedir(dirp);
	return (0);
}

static void	set_full_cmd_name(const char *dir_path, t_command *cmd)
{
	size_t	len;
	char	*full_name;

	len = ft_strlen(dir_path) + ft_strlen(cmd->cmd_name);
	if (!(full_name = (char*)ft_calloc(len + 2, sizeof(*full_name))))
		errman(ENOMEM, NULL);
	ft_strlcat(full_name, dir_path, len + 2);
	ft_strlcat(full_name, "/", len + 2);
	ft_strlcat(full_name, cmd->cmd_name, len + 2);
	free(cmd->cmd_name);
	cmd->cmd_name = full_name;
}

int			is_ok_set_cmd_exec_name(t_command *cmd, t_env *env)
{
	struct stat	f_stat;
	char		**path_tab;
	int			i;
	const char	*value;

	if (!(stat(cmd->cmd_name, &f_stat)))
		return (1);
	value = env->get_value(env, "PATH");
	if (!value)
		return (0);
	if (!(path_tab = ft_split(value, ':')))
		errman(ENOMEM, NULL);
	i = -1;
	while (path_tab[++i])
	{
		if (does_dir_contains_cmd(path_tab[i], cmd->cmd_name))
		{
			set_full_cmd_name(path_tab[i], cmd);
			ft_free_tab((void **)path_tab);
			return (1);
		}
	}
	ft_free_tab((void **)path_tab);
	return (0);
}
