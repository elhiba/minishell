/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:59:36 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/31 19:50:09 by moel-hib         ###   ########.fr       */
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
		return (0);
	}
}

void	update_pwd(char *old_pwd, char *old_cwd, t_cmd *data)
{
	char		*cwd;
	t_export	*export;

	export = NULL;
	cwd = NULL;
	if (old_pwd && get_cwd(&cwd))
	{
		parse_export(&export, ft_strjoin("OLDPWD=", old_pwd));
		if (export_exist(export, &data->data->env))
			;
		else
		{
			if (old_cwd)
				parse_export(&export, ft_strjoin("OLDPWD=", old_cwd));
			add_to_env(export, &data->data->env);
		}
		parse_export(&export, ft_strjoin("PWD=", cwd));
		export_exist(export, &data->data->env);
	}
	else
		unset_filter("OLDPWD", &data->data->env);
}

int	cd_errors(char *path, char *old_pwd, char *old_cwd, t_cmd *data)
{
	if (path && !path[0])
		return (data->data->last_exit_code = 0, 1);
	if (!path)
	{
		if (!sea_ret(data->data->env, "HOME"))
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (data->data->last_exit_code = 1, 1);
		}
		if (chdir(sea_ret(data->data->env, "HOME")) == -1)
		{
			perror("minishell: cd: chdir");
			return (data->data->last_exit_code = 1, 1);
		}
		update_pwd(old_pwd, old_cwd, data);
		return (data->data->last_exit_code = 0, 1);
	}
	else if (data->argv[1])
	{
		write(2, "minishell: too many arguments\n", 30);
		return (data->data->last_exit_code = 1, 2);
	}
	return (0);
}

/*
 * We will try to make it performant handling more stuff like:
 *	[cd - and updating the old pwd]
 * */
int	do_cd(t_cmd *data)
{
	char	*path;
	char	*old_pwd;
	char	*old_cwd;
	int		ret;

	path = *(++data->argv);
	old_cwd = NULL;
	get_cwd(&old_cwd);
	old_pwd = sea_ret(data->data->env, "PWD");
	ret = cd_errors(path, old_pwd, old_cwd, data);
	if (ret)
		return (ret);
	else if (chdir(path) == -1)
	{
		perror(ft_strjoin("minishell: cd: ", path));
		data->data->last_exit_code = 1;
		return (1);
	}
	update_pwd(old_pwd, old_cwd, data);
	data->data->last_exit_code = 0;
	return (1);
}
