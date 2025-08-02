/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:33:18 by moel-hib          #+#    #+#             */
/*   Updated: 2025/08/02 11:41:03 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**copy_env(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = ft_collector(sizeof(char *) * (i + 1), ALLOC);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	ft_setenv(char ***env, char *key, char *val)
{
	int		i;
	char	**new_env;
	char	*entry;

	entry = ft_strjoin3(key, "=", val);
	if (!entry)
		return ;
	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp((*env)[i], key, ft_strlen(key))
			&& (*env)[i][ft_strlen(key)] == '=')
		{
			free((*env)[i]);
			(*env)[i] = entry;
			return ;
		}
	}
	new_env = ft_collector(sizeof(char *) * (i + 2), ALLOC);
	i = -1;
	while ((*env)[++i])
		new_env[i] = (*env)[i];
	new_env[i++] = entry;
	new_env[i] = NULL;
	(free(*env), *env = new_env);
}

char	*ft_getenv(char *key, t_data *data)
{
	char	**env;
	int		i;
	int		keylen;

	i = 0;
	keylen = ft_strlen(key);
	env = data->env;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, keylen) == 0 && env[i][keylen] == '=')
		{
			return (env[i] + keylen + 1);
		}
		i++;
	}
	return (NULL);
}
