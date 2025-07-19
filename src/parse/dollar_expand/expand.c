/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:06:51 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/19 11:45:40 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	extract_variable_name(char *token, t_env *env)
{
	int	i;
	int	j;
	int	len;

	(1) && (i = 0, j = 0, len = 0);
	while (token[len] && is_alnum_(token[len]) == true)
		len++;
	env->name = ft_collector(sizeof(char) * (len + 1), ALLOC);
	if (!env->name)
		return ;
	i = 0;
	while (token[i] && is_alnum_(token[i]) == true)
	{
		env->name[i] = token[i];
		i++;
	}
	env->name[i] = '\0';
	env->name_len = len;
	env->value = NULL;
	env->value_len = 0;
	(1) && (i = 0, j = 0);
}

void	get_env_value(char **envp, t_env *env)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env->name, env->name_len) == 0
			&& envp[i][env->name_len] == '=')
		{
			env->value = ft_strdup(envp[i] + env->name_len + 1);
			env->value_len = ft_strlen(env->value);
			return ;
		}
		i++;
	}
	env->value = ft_strdup("");
	env->value_len = 0;
}

void	check_prev(t_token *current)
{
	t_token	*prev;

	prev = current->prev;
	while (prev)
	{
		if (!current->is_not_splittable && prev->is_not_splittable && \
			!prev->is_space_next)
			prev->is_not_splittable = 0;
		else if (prev->is_not_splittable && !prev->is_space_next)
			current->is_not_splittable = 1;
		else if (current->is_not_splittable && !prev->is_space_next)
			prev->is_not_splittable = 1;
		prev = prev->prev;
	}
	while (current)
	{
		if (current->is_not_splittable && current->next && \
			!current->is_space_next)
			current->next->is_not_splittable = 1;
		else if (!current->is_not_splittable && current->next && \
				!current->is_space_next)
			current->next->is_not_splittable = 0;
		current = current->next;
	}
}

void	expand_variable(t_token *current, t_data *data, char **envp, \
					char **token)
{
	t_env	*env;
	char	*expanded_token;
	char	*exit_code;
	void	**small_data;

	env = ft_collector(sizeof(t_env), ALLOC);
	expanded_token = ft_strdup("");
	exit_code = ft_itoa(data->last_exit_code);
	if (!env)
		return ;
	small_data = ft_collector(sizeof(void *) * 5, ALLOC);
	small_data[0] = env;
	small_data[1] = &expanded_token;
	small_data[2] = exit_code;
	small_data[3] = envp;
	small_data[4] = NULL;
	current->key = ft_strdup(current->arg);
	while (**token)
		expand_verifier(current, token, small_data);
	if (!current->is_dquote)
		check_prev(current);
	current->value = ft_strdup(expanded_token);
	*token = expanded_token;
}

void	check_and_expand(t_token **head, t_data *data, char **envp)
{
	t_token	*current;
	t_token	*tmp;

	current = *head;
	while (current)
	{
		if (current->prev && !ft_strcmp(current->prev->arg, "<<"))
		{
			tmp = current;
			while (tmp)
			{
				tmp->not_expandable = 1;
				if (tmp->is_space_next)
					break ;
				tmp = tmp->next;
			}
		}
		if (check_is_expandable(current) && !current->is_squote && \
			!current->not_expandable)
		{
			expand_variable(current, data, envp, &current->arg);
			current->is_env_var = 1;
		}
		current = current->next;
	}
}
