/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:55:28 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/19 16:49:32 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_cmd_name(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
		i++;
	while (buffer[i] != '/' && i != 0)
		i--;
	if (buffer[i] == '/')
		i++;
	return (buffer + i);
}

int	is_a_builtin(char *name)
{
	if (!name)
		return (0);
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	else if (ft_strcmp(name, "echo") == 0)
		return (1);
	else if (ft_strcmp(name, "env") == 0)
		return (1);
	else if (ft_strcmp(name, "exit") == 0)
		return (1);
	else if (ft_strcmp(name, "export") == 0)
		return (1);
	else if (ft_strcmp(name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(name, "unset") == 0)
		return (1);
	return (0);
}

char	*handle_empty_path(char *cmd_name)
{
	char	*tmp;

	tmp = ft_strjoin("./", cmd_name);
	if (access(tmp, X_OK) == 0 && !is_a_directory(tmp))
		return (tmp);
	else if (access(tmp, F_OK) == 0)
		return (tmp);
	return (NULL);
}

char	**cp_stock(char *cmd_name, char **path_stock)
{
	char	**tmp_stock;
	char	*new_name;
	int		i;

	i = 0;
	while (path_stock[i])
		i += 1;
	tmp_stock = ft_collector(sizeof(char *) * (i + 1), ALLOC);
	i = 0;
	while (path_stock[i])
	{
		new_name = ft_strjoin("/", cmd_name);
		tmp_stock[i] = ft_strjoin(path_stock[i], new_name);
		i++;
	}
	tmp_stock[i] = NULL;
	return (tmp_stock);
}

char	*check_for_cmd_existence(char **tmp_stock)
{
	int	i;

	i = 0;
	while (tmp_stock[i])
	{
		if (access(tmp_stock[i], X_OK) == 0 && !is_a_directory(tmp_stock[i]))
			return (tmp_stock[i]);
		i++;
	}
	i = 0;
	while (tmp_stock[i])
	{
		if (access(tmp_stock[i], F_OK) == 0)
			return (tmp_stock[i]);
		i++;
	}
	return (NULL);
}
