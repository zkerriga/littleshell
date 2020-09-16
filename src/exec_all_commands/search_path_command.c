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

static int	does_dir_contains_cmd(const char *path, const char *name)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				len;

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
	int		len;
	char	*full_name;

	len = ft_strlen(dir_path) + ft_strlen(cmd->cmd_name);
	full_name = (char*)ft_calloc(len + 2, sizeof(*full_name));
	ft_strlcat(full_name, dir_path, len + 2);
	ft_strlcat(full_name, "/", len + 2);		// TODO: if (last char of dir) or (first char of cmd->name) has '/'??
	ft_strlcat(full_name, cmd->cmd_name, len + 2);
	free(cmd->cmd_name);
	cmd->cmd_name = full_name;
}

int is_ok_set_cmd_exec_name(t_command *cmd, t_env *env)
{
	struct stat	f_stat;
	char 		**path_tab;
	int 		i;

	if (!(stat(cmd->cmd_name, &f_stat)))
		return (1);
	path_tab = ft_split(env->get_value(env, "PATH"), ':'); // TODO: add error managment // TODO: if dir name contains ':'??
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

