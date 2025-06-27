/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:42:28 by slasfar           #+#    #+#             */
/*   Updated: 2025/06/27 13:34:51 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char *cp_buffer(char *buffer)
{
	int i = 0;
	char *new;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	new = malloc(i + 1);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		new[i] = buffer[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*dir_name()
{
	char	*cwd;
	char	*prompt;
	int		i = 0;

	cwd = getcwd(NULL, 0);
	while (cwd[i])
		i++;
	while (cwd[i] != '/' && i != 0)
		i--;
	return (cwd + i + 1);
}

char	*get_sha(char *buffer)
{
	int i = 0;
	char	*new = malloc(8);
	while (i < 7)
	{
		new[i] = buffer[i];
		i++;
	}
	buffer[i] = '\0';
	return (new);
}

char *get_head(int *type)
{
	char *buffer = malloc(1000);
	int	fd;

	fd = open("./.git/HEAD", O_RDONLY);
	read(fd, buffer, 1000);
	int i = 0;
	if (ft_strncmp(buffer, "ref", 3) != 0)
	{
		if (type)
			*type = 1337;
		return (buffer = get_sha(buffer));
	}
	while (buffer[i])
		i++;
	while (buffer[i] != '/' && i != 0)
		i--;
	i++;
	if (type)
		*type = 42;
	return (buffer + i);
}


int	find_git()
{
	struct stat buffer;
	int			type;

	if (stat("./.git", &buffer) == 0 && S_ISDIR(buffer.st_mode))
	{
		if (access("./.git/HEAD", F_OK) != 0)
			return (0);
		char	*head = cp_buffer(get_head(&type));
		if (type == 42)
		{
			char *file = ft_strjoin("./.git/refs/heads/", head);
			if (access(file, F_OK) != 0)
				return (0);
		}
		else if (type == 1337)
		{
			if (access("./.git/objects", F_OK) != 0)
				return (0);
		}
		return (1);
	}
	return (0);
}


char	*prompt_builder(t_data *data)
{
	char	*dirname;
	char	*prompt;
	char	*git_branch;
	char	*head;
	char	*arrow;

	dirname = dir_name();
	if (find_git() == 1)
	{
		head = cp_buffer(get_head(NULL));
		head = ft_strjoin("\001\033[1m\033[31m\002", ft_strjoin(head, "\001\033[0m\033[1m\033[34m)\033[0m\002 "));
		dirname = ft_strjoin("\001\033[1m\033[36m\002", ft_strjoin(dirname, "\001\033[0m\002"));
		git_branch = ft_strjoin(" \001\033[1m\033[34m\002git:(\001\033[0m\002", head);
		if (data->last_exit_code == 0)
			arrow = ft_strjoin("\001\033[1m\033[32m\002⮕\001\033[0m\002", " ");
		else
			arrow = ft_strjoin("\001\033[1m\033[31m\002⮕\001\033[0m\002", " ");
		prompt = ft_strjoin(dirname, ft_strjoin(git_branch, arrow));
		return (prompt);
	}
	else
	{
		prompt = ft_strjoin("\001\033[1m\033[36m\002", ft_strjoin(dirname, " \001\033[0m\033[1m\033[33m\002⮕ \001\033[0m\002"));
		return (prompt);
	}
}
