/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:30:22 by sel-maaq          #+#    #+#             */
/*   Updated: 2025/06/20 17:41:49 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**remove_var(char **env, char *key);

int	do_unset(t_cmd *data)
{
//	t_token	*args;
//
//	args = data->token_list->next;
//	while (args)
//	{
//		if (ft_getenv(args->arg, data))
//		{
//			data->env = remove_var(data->env, args->arg);
//			if (!data->env)
//				error_handler("unset malloc error", data);
//		}
//		args = args->next;
//	}
//	data->last_exit_code = 0;
//	return (1);
}

char	**remove_var(char **env, char *key)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (NULL);
	i = -1;
	j = 0;
	while (env[++i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)) != 0
			|| env[i][ft_strlen(key)] != '=')
			new_env[j++] = env[i];
		else
			free(env[i]);
	}
	new_env[j] = NULL;
	free(env);
	return (new_env);
}
