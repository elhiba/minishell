/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 14:59:36 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/14 15:40:07 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * We will try to make it performant handling more stuff like [cd - and updating the old pwd]
 * */

int	do_cd(t_cmd *data)
{
	char	*path;

	path = *(++data->argv);
	if (data->argv[1])
	{
		write(2, "minishell: too many arguments\n", 31);
		data->data->last_exit_code = 1;
		return (2);
	}
	if (!path)
	{
		if (chdir(sea_ret(data->data->env, "HOME")) == -1)
			write(2, "minishell: cd: HOME not set\n", 28);
		data->data->last_exit_code = 1;
	}
	else if (chdir(path) == -1)
	{
		perror(ft_strjoin("minishell: cd: ", path));
		data->data->last_exit_code = 1;
	}
	data->data->last_exit_code = 0;
	return (1);
}
