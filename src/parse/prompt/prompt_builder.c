/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:42:28 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/21 09:57:28 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		prompt = ft_strjoin(prompt, " \x7f");
	return (prompt);
}

static char	*build_simple_prompt(int exit_code, \
							char *colored_dirname, int is_tilde)
{
	char	*exit_code_part;
	char	*arrow;
	char	*prompt;

	exit_code_part = format_exit_code(exit_code);
	arrow = get_status_arrow(exit_code);
	prompt = ft_strjoin(exit_code_part, colored_dirname);
	if (!is_tilde)
	{
		prompt = ft_strjoin(prompt, " \x7f");
		prompt = ft_strjoin(prompt, arrow);
	}
	else
		prompt = ft_strjoin(prompt, " \x7f");
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
	char		*dirname;
	static int	flag;
	int			is_tilde;

	is_tilde = 0;
	if (!flag)
	{
		old_prompt = ft_strdup("minishell");
		flag = 1;
	}
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
