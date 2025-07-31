/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_checker2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:26:51 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/31 20:09:40 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_detached(char *git_root)
{
	char	*objects_path;

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
int	is_git_valid(void)
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

char	*build_git_part(void)
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

char	*get_status_arrow(int exit_code)
{
	if (exit_code == 0)
		return (ft_strjoin("\001\e[1;32m➜\e[0m\002", " \x7f"));
	else
		return (ft_strjoin("\001\e[1;31m➜\e[0m\002", " \x7f"));
}

char	*format_exit_code(int exit_code)
{
	char	*code_str;
	char	*colored_code;
	char	*bracket_code;

	code_str = ft_itoa(exit_code);
	if (exit_code == 0)
		colored_code = ft_strjoin("\001\e[1;32m\002", code_str);
	else
		colored_code = ft_strjoin("\001\e[1;31m\002", code_str);
	colored_code = ft_strjoin(colored_code, "\001\e[0m\002");
	bracket_code = ft_strjoin("\001[\002", colored_code);
	bracket_code = ft_strjoin(bracket_code, "] ");
	return (bracket_code);
}
