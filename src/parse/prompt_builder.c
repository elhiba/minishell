/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:42:28 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/15 17:14:37 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define MAX_PATH_SIZE 4096

static char	*cp_buffer(char *buffer)
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
static char	*relative_name(char *path)
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
static char	*dir_name(t_data *data)
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
static char	*get_parent_dir(char *current_path)
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
static char	*check_git(char *dir_path)
{
	char		*git_path;
	struct stat	stat_buf;

	git_path = ft_strjoin(dir_path, "/.git");
	if (git_path && stat(git_path, &stat_buf) == 0 && S_ISDIR(stat_buf.st_mode))
		return (git_path);
	return (NULL);
}

/*
	this function check all the parent directories for ".git"
*/
static char	*search_for_git(void)
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
			break;
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

static char	*read_head(int *git_type)
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

static int	validate_branch_ref(char *git_root, char *head)
{
	char	*ref_file;

	ref_file = ft_strjoin(git_root, "/refs/heads/");
	ref_file = ft_strjoin(ref_file, head);
	if (access(ref_file, F_OK) == 0)
		return (1);
	return (0);
}

static int	check_detached(char *git_root)
{
	char	*objects_path;
	struct stat	buffer;

	objects_path = ft_strjoin(git_root, "/objects");
	if (is_a_directory(objects_path))
		return (1);
	return (0);
}

/*
	Validates if current directory is within a valid Git repository.
	Checks for .git directory in parent dirs.
	Returns 1 if valid Git repo found, 0 otherwise.
	Used by prompt builder to show Git info in shell prompt.
*/
static int	is_git_valid(void)
{
	char	*git_path;
	int		git_type;
	char	*head;

	git_path = search_for_git();
	if (!git_path)
		return (0);
	head = cp_buffer(read_head(&git_type));
	if (!head)
		return (0);
	if (git_type == 42)
		return (validate_branch_ref(git_path, head));
	else if (git_type == 1337)
		return (check_detached(git_path));
	return (0);
}

static char	*build_git_part(void)
{
	char	*head;
	char	*git_info;
	char	*git_prefix;

	head = cp_buffer(read_head(NULL));
	if (!head)
		return (ft_strdup(""));
	head = ft_strjoin("\001\033[1m\033[31m\002", head);
	head = ft_strjoin(head, "\001\033[0m\033[1m\033[34m)\033[0m\002");
	git_prefix = ft_strjoin(" \001\033[1m\033[34m\002git:(\001\033[0m\002", head);
	git_info = ft_strjoin(git_prefix, " ");
	if (!git_info)
		return (ft_strdup(""));
	return (git_info);
}

static char	*get_status_arrow(int exit_code)
{
	if (exit_code == 0)
		return (ft_strjoin("\001\033[1;32m\002➜\001\033[0m\002", " "));
	else
		return (ft_strjoin("\001\033[1;31m\002➜\001\033[0m\002", " "));
}

static char	*format_exit_code(int exit_code)
{
	char	*code_str;
	char	*colored_code;
	char	*bracket_code;

	code_str = ft_itoa(exit_code);
	if (exit_code == 0)
		colored_code = ft_strjoin("\001\033[1;32m\002", code_str);
	else
		colored_code = ft_strjoin("\001\033[1;31m\002", code_str);
	colored_code = ft_strjoin(colored_code, "\001\033[0m\002");
	bracket_code = ft_strjoin("[", colored_code);
	bracket_code = ft_strjoin(bracket_code, "] ");
	return (bracket_code);
}

static char	*build_git_prompt(t_data *data, char *colored_dirname, int is_tilde)
{
	char	*exit_code_part;
	char	*git_part;
	char	*arrow;
	char	*prompt;

	exit_code_part = format_exit_code(data->last_exit_code);
	git_part = build_git_part();
	arrow = get_status_arrow(data->last_exit_code);
	prompt = ft_strjoin(exit_code_part, colored_dirname);
	prompt = ft_strjoin(prompt, git_part);
	if (!is_tilde)
		prompt = ft_strjoin(prompt, arrow);
	else 
		prompt = ft_strjoin(prompt, " ");
	return (prompt);
}

static char	*build_simple_prompt(int exit_code, char *colored_dirname, int is_tilde)
{
	char	*exit_code_part;
	char	*arrow;
	char	*prompt;

	exit_code_part = format_exit_code(exit_code);
	arrow =  get_status_arrow(exit_code);
	prompt = ft_strjoin(exit_code_part, colored_dirname);
	if (!is_tilde)
	{
		prompt = ft_strjoin(prompt, " ");
		prompt = ft_strjoin(prompt, arrow);
	}
	else 
		prompt = ft_strjoin(prompt, " ");
	return (prompt);
}

char	*build_dir_name(t_data *data, int *is_tilde)
{
	char	*dirname;

	dirname = dir_name(data);
	if (!dirname)
		return (NULL);
	else if (!ft_strcmp(dirname, "~"))
		*is_tilde = 1;
	dirname = ft_strjoin("\001\033[1;36m\002", dirname);
	dirname = ft_strjoin(dirname, "\001\033[0m\002");
	return (dirname);
}

char	*prompt_builder(t_data *data)
{
	static char	*old_prompt;
	char	*dirname;
	int		is_tilde;

	is_tilde = 0;
	dirname = build_dir_name(data, &is_tilde);
	if (!dirname)
		dirname = old_prompt;
	else
		old_prompt = dirname;
	if (is_git_valid())
		return (build_git_prompt(data, dirname, is_tilde));
	else
		return (build_simple_prompt(data->last_exit_code, dirname, is_tilde));
}
