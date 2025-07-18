/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_checker1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:13:54 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/18 19:26:29 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	this function check all the parent directories for ".git"
*/
char	*search_for_git(void)
{
	char	*cwd;
	char	*current_path;
	char	*git_path;

	cwd = ft_collector(MAX_PATH_SIZE, ALLOC);
	if (!getcwd(cwd, MAX_PATH_SIZE))
		return (NULL);
	current_path = ft_strdup(cwd);
	while (ft_strcmp(current_path, "/"))
	{
		git_path = check_git(current_path);
		if (git_path)
			return (git_path);
		current_path = get_parent_dir(current_path);
		if (!current_path)
			break ;
	}
	if (!ft_strcmp(current_path, "/"))
		return (NULL);
	return (current_path);
}

static char	*extract_branch(char *buffer)
{
	char	*result;
	int		i;

	i = 0;
	while (buffer[i])
		i++;
	while (i > 0 && buffer[i] != '/')
		i--;
	i++;
	result = cp_buffer(buffer + i);
	return (result);
}

static char	*read_head_file(char *head_path)
{
	int		fd;
	char	*buffer;

	buffer = ft_collector(1000, ALLOC);
	fd = open(head_path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (read(fd, buffer, 999) <= 0)
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	return (buffer);
}

char	*read_head(int *git_type)
{
	char	*git_root;
	char	*head_path;
	char	*buffer;

	git_root = search_for_git();
	if (!git_root)
		return (NULL);
	head_path = ft_strjoin(git_root, "/HEAD");
	buffer = read_head_file(head_path);
	if (!buffer)
		return (NULL);
	if (ft_strncmp(buffer, "ref", 3) != 0)
	{
		if (git_type)
			*git_type = 1337;
		ft_strlcpy(buffer, buffer, 8);
		return (buffer);
	}
	if (git_type)
		*git_type = 42;
	return (extract_branch(buffer));
}

int	validate_branch_ref(char *git_root, char *head)
{
	char	*ref_file;

	ref_file = ft_strjoin(git_root, "/refs/heads/");
	ref_file = ft_strjoin(ref_file, head);
	if (access(ref_file, F_OK) == 0)
		return (1);
	return (0);
}
