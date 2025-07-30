/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:08:25 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/30 22:01:45 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_env(char *var, char ***env)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_env = ft_collector(sizeof(char *) * (ft_arglen(*env) + 1), ALLOC);
	while ((*env)[i])
	{
		if (ft_strncmp(var, (*env)[i], ft_strlen(var)) == 0)
			i++;
		new_env[j] = (*env)[i];
		if (!(*env)[i])
			break ;
		i++;
		j++;
	}
	*env = new_env;
}

int	unset_filter(char *arg, char ***env)
{
	char	*full_unset;
	int		i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp(arg, (*env)[i], ft_strlen(arg)) == 0)
		{
			remove_env(arg, env);
			break ;
		}
		i++;
	}
	return (0);
}

int	do_unset(t_cmd *data)
{
	char	**ptr;
	int		i;

	i = 0;
	ptr = ++data->argv;
	while (ptr[i])
	{
		unset_filter(ptr[i], &data->data->env);
		i++;
	}
	data->data->last_exit_code = 0;
	return (1);
}
