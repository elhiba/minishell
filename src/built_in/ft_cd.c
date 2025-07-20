/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:59:36 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/20 20:52:47 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	et_old_pwd(char **old_path)
{
	char	*buffer;

	buffer = ft_collector(PATH_MAX, ALLOC);
	if (getcwd(buffer, PATH_MAX))
	{
		*old_path = buffer;
		return (1);
	}
	else
		return (0);
}

int	get_cwd(char **cwd)
{
	char	*buffer;

	buffer = ft_collector(PATH_MAX, ALLOC);
	if (getcwd(buffer, PATH_MAX))
	{
		*cwd = buffer;
		return (1);
	}
	else
	{
		perror("minishell: cd");
		return (0);
	}
}

void	update_pwd(char *old_pwd, t_cmd *data)
{
	char	*cwd;

	cwd = NULL;
	if (old_pwd)
	{
		if (get_cwd(&cwd))
		{
			exist(ft_strjoin("OLDPWD=", old_pwd), &data->data->env);
			exist(ft_strjoin("PWD=", cwd), &data->data->env);
		}
	}
	else 
		unset_filter("OLDPWD", &data->data->env);
}
/*
 * We will try to make it performant handling more stuff like:
 *	[cd - and updating the old pwd]
 * */
int	do_cd(t_cmd *data)
{
	char		*path;
	char		*old_pwd;
	char		*cwd;

	path = *(++data->argv);
	old_pwd = sea_ret(data->data->env, "PWD");
	if (path && !path[0])
	{
		data->data->last_exit_code = 0;
		return (1);
	}
	if (!path)
	{
		if (chdir(sea_ret(data->data->env, "HOME")) == -1)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			data->data->last_exit_code = 1;
			return (1);
		}
		update_pwd(old_pwd, data);
		data->data->last_exit_code = 0;
		return (1);
	}
	else if (data->argv[1])
	{
		write(2, "minishell: too many arguments\n", 31);
		data->data->last_exit_code = 1;
		return (2);
	}
	else if (chdir(path) == -1)
	{
		perror(ft_strjoin("minishell: cd: ", path));
		data->data->last_exit_code = 1;
		return (1);
	}
	update_pwd(old_pwd, data);
	data->data->last_exit_code = 0;
	return (1);
}
