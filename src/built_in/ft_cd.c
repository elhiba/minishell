/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:59:36 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/20 17:51:30 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args(t_token *token_list)
{
	int	i;

	i = 0;
	while (token_list)
	{
		i++;
		token_list = token_list->next;
	}
	return (i - 1);
}

static char	*get_cd_target(t_data *data)
{
	char	*arg;

	if (data->token_list->next)
		arg = data->token_list->next->arg;
	else
		arg = NULL;
	if (!arg)
	{
		arg = ft_getenv("HOME", data);
		if (!arg)
			printf("cd: HOME not set\n");
	}
	else if (!ft_strcmp(arg, "-"))
	{
		arg = ft_getenv("OLDPWD", data);
		if (!arg)
			printf("cd: OLDPWD not set\n");
	}
	return (arg);
}

static void	update_pwd(t_data *data, char *old_pwd, char *cd_arg)
{
	char	new_pwd[4096];
	char	*tmp;

	ft_setenv(&data->env, "OLDPWD", old_pwd);
	if (getcwd(new_pwd, sizeof(new_pwd)))
		ft_setenv(&data->env, "PWD", new_pwd);
	else
	{
		tmp = ft_strjoin3(ft_getenv("PWD", data), "/", cd_arg);
		if (tmp)
		{
			ft_setenv(&data->env, "PWD", tmp);
			free(tmp);
		}
		perror("cd: error retrieving current directory:"
			"getcwd: cannot access parent directories");
	}
}

int	do_cd(t_cmd *data)
{


	return (1);
}
