/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:24:26 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/23 01:31:38 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ex a += 7 ->  a=77 || a=7 // = labouda

int		is_valid_key(char *key);
void	print_sorted_env(char **env);

// did allll of export except this (up)
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
			if (is_valid_key(key))
				ft_setenv(&data->env, key, value);
			else
				printf("export: `%s': not a valid identifier\n", args->arg);
			(free(key), free(value));
		}
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

int	is_valid_key(char *key)
{
	int	i;

	if (!key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
