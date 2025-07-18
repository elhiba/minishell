/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_checker0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 18:38:02 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/18 19:26:36 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*cp_buffer(char *buffer)
{
	int		i;
	char	*new;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	new = ft_collector(i + 1, ALLOC);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		new[i] = buffer[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

/*
	extract the directory name from the absolute path
	eg: "/home/user/minishell" -> "minishell"
*/
char	*relative_name(char *path)
{
	int		i;
	char	*dirname;

	dirname = NULL;
	i = ft_strlen(path) - 1;
	while (i > 0 && path[i] != '/')
		i--;
	dirname = ft_strdup(path + i + 1);
	return (dirname);
}

/*
	this function retrieve the current working directory name
	return values:
		NULL: in case of failure.
		dirname: relative path of the current working directory;
		eg: "/home/user/minishell" -> "minishell"
*/
char	*dir_name(t_data *data)
{
	char	*cwd;
	char	*home;

	cwd = ft_collector(MAX_PATH_SIZE, ALLOC);
	if (!getcwd(cwd, MAX_PATH_SIZE))
		return (NULL);
	home = sea_ret(data->env, "HOME");
	if (home && ft_strcmp(cwd, home) == 0)
		return (ft_strdup("~"));
	if (ft_strcmp(cwd, "/") == 0)
		return (ft_strdup("/"));
	return (relative_name(cwd));
}

/*
	move to parrent dir
*/
char	*get_parent_dir(char *current_path)
{
	char	*parent_path;
	int		i;

	i = 0;
	while (current_path[i])
		i++;
	i--;
	while (i > 0 && current_path[i] != '/')
		i--;
	if (i == 0)
		return (NULL);
	i += 1;
	parent_path = ft_collector(i, ALLOC);
	ft_strlcpy(parent_path, current_path, i);
	return (parent_path);
}

/*
	if valid returns dir_path if not return NULL
*/
char	*check_git(char *dir_path)
{
	char		*git_path;
	struct stat	stat_buf;

	git_path = ft_strjoin(dir_path, "/.git");
	if (git_path && stat(git_path, &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
		return (git_path);
	return (NULL);
}
