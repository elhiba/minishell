/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:37:28 by sel-maaq          #+#    #+#             */
/*   Updated: 2025/05/02 21:53:24 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		is_valid_key(char *key, t_data *data);
void	print_sorted_env(char **env);

int	do_export(t_data *data)
{
	t_token	*args;
	char	*found;
	char	*key;
	char	*value;

	args = data->token_list->next;
	if (!args)
		return (print_sorted_env(data->env), 1);
	while (args)
	{
		found = ft_strchr(args->arg, '=');
		if (found)
		{
			key = ft_substr(args->arg, 0, found - args->arg);
			value = ft_substr(args->arg, (found - args->arg) + 1,
					ft_strlen(found + 1));
			if (is_valid_key(key, data))
				ft_setenv(&data->env, key, value);
			(free(key), free(value));
		}
		else
			is_valid_key(args->arg, data);
		args = args->next;
	}
	return (1);
}

void	print_sorted_env(char **env)
{
	char	**env_cpy;
	char	*equal_sign;
	int		i;

	env_cpy = copy_env(env);
	sort_env(env_cpy);
	i = 0;
	while (env_cpy[i])
	{
		equal_sign = ft_strchr(env_cpy[i], '=');
		if (equal_sign)
		{
			*equal_sign = '\0';
			printf("declare -x %s=\"%s\"\n", env_cpy[i], equal_sign + 1);
			*equal_sign = '=';
		}
		i++;
	}
	free_d_arr(env_cpy);
}

int	is_valid_key(char *key, t_data *data)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
	{
		printf("export: '%s': not a valid identifier\n", key);
		data->last_exit_code = 1;
		return (0);
	}
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			printf("export: '%s': not a valid identifier\n", key);
			data->last_exit_code = 1;
			return (0);
		}
		i++;
	}
	return (1);
}
