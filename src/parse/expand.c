/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:06:51 by slasfar           #+#    #+#             */
/*   Updated: 2025/06/01 10:25:07 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_digit_(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	is_alpha_(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (true);
	return (false);
}

bool	is_alnum_(char c)
{
	if ((is_alpha_(c) || is_digit_(c)
		|| c == '_') && c != '$' && c != '\0')
		return (true);
	return (false);
}

bool	is_white_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}


int	check_is_expandable(char *buffer)
{
	int i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '$' && !is_white_space(buffer[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

//a function that will trim a substring from the start of a string
char	*ft_trim(char *str, int len)
{
	int		i;
	char	*trimmed_str;

	i = 0;
	trimmed_str = ft_collector(sizeof(char) * (ft_strlen(str) - len + 1), ALLOC);
	if (!trimmed_str)
		return (NULL);
	while (str[i + len])
	{
		trimmed_str[i] = str[i + len];
		i++;
	}
	trimmed_str[i] = '\0';
	return (trimmed_str);
}

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

// This function will expand the variable in the token for eg:
//"Hello $USER World" to "Hello slasfar World"

/*
the logic of the function is as follows:
check if the envirement variable is valid to expand
use strjoin to join parts of the token
use trim to remove the parts that you already added to the expanded token
it could be more than one variable in the token
so we need to loop over the token
*/
void	expand_variable(char **envp, char **token)
{
	t_env	*env;
	char	*expanded_token;

	env = ft_collector(sizeof(t_env), ALLOC);
	expanded_token = ft_strdup("");
	if (!env)
		return ;
	while (**token)
	{
		if (**token == '$' && is_alnum_(*(*token + 1)) == true)
		{
			extract_variable_name(*token + 1, env);
			get_env_value(envp, env);
			expanded_token = ft_strnjoin(expanded_token, env->value, env->value_len);
			*token = ft_trim(*token, env->name_len + 1);
			//free(env->name);
		}
		else
		{
			expanded_token = ft_strnjoin(expanded_token, *token, 1);
			*token = ft_trim(*token, 1);
		}
	}
	*token = expanded_token;
}

void check_and_expand(t_token **head, char **envp)
{
	t_token *current;

	current = *head;
	while (current)
	{
		if (check_is_expandable(current->arg) && !current->is_squote)
		{
			expand_variable(envp, &current->arg);
			current->is_env_var = 1;
			current->is_squote = 1;
		}
		current = current->next;
	}
}