/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:55:28 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/30 22:20:21 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_full_path(char **path_stock, char *cmd_name, int *not_found)
{
	int		i;
	char	**tmp_stock;
	char	*cmd_path;
	char	*tmp;

	i = 0;
	cmd_path = NULL;
	while (path_stock[i])
		i += 1;
	if (i == 0)
	{
		tmp = handle_empty_path(cmd_name);
		if (tmp)
			return (tmp);
	}
	tmp_stock = cp_stock(cmd_name, path_stock);
	i = 0;
	cmd_path = check_for_cmd_existence(tmp_stock);
	if (cmd_path)
		return (cmd_path);
	if (!is_a_builtin(cmd_name))
		*not_found = 1;
	return (cmd_name);
}

int	check_absolute_path(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

int	empty_env_var(t_token *current)
{
	if (current->is_env_var && !is_redir(current)
		&& !current->prev && !current->next
		&& !current->is_dquote && !current->arg[0])
		return (1);
	return (0);
}

int	is_valid_cmd_name(t_token *current)
{
	if ((current->is_dquote
			|| current->is_word
			|| current->is_squote
			|| current->is_env_var)
		&& !(current->is_env_var
			&& !current->is_dquote
			&& !current->arg[0])
		&& !is_redir(current)
		&& !current->is_ambiguous)
		return (1);
	return (0);
}
