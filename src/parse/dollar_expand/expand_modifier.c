/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_modifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 11:44:41 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/19 11:44:52 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	variable_merger(t_token *current, char **token, void **data)
{
	t_env	*env;
	char	**expanded_token;
	char	**envp;

	env = (t_env *)data[0];
	expanded_token = (char **)data[1];
	envp = (char **)data[3];
	current->is_not_splittable = 0;
	extract_variable_name(*token + 1, env);
	get_env_value(envp, env);
	*expanded_token = ft_strnjoin(*expanded_token, env->value, env->value_len);
	*token = ft_trim(*token, env->name_len + 1);
}

void	expand_verifier(t_token *current, char **token, void **data)
{
	char	**expanded_token;
	char	*exit_code;

	exit_code = (char *)data[2];
	expanded_token = (char **)data[1];
	if ((**token == '$' && !current->is_dquote && *(*token + 1) != '?' \
		&& !is_alnum_(*(*token + 1))))
		current->is_not_splittable = 1;
	if (**token == '$' && *(*token + 1) == '?')
	{
		*expanded_token = ft_strnjoin(*expanded_token, exit_code, \
							ft_strlen(exit_code));
		*token = ft_trim(*token, 2);
	}
	else if ((**token == '$' && !ft_isdigit(*(*token + 1)) \
		&& is_alnum_(*(*token + 1)) == true))
		variable_merger(current, token, data);
	else
	{
		*expanded_token = ft_strnjoin(*expanded_token, *token, 1);
		*token = ft_trim(*token, 1);
	}
}
