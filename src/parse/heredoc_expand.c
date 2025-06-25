/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:06:51 by slasfar           #+#    #+#             */
/*   Updated: 2025/06/24 15:37:19 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_it_expandable(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if ((buffer[i] == '$' && !is_digit_(buffer[i + 1]) && !is_white_space(buffer[i + 1])))
			return (1);
		i++;
	}
	return (0);
}

/*
	this function is the same as the normal expanding function, just without all the eadge cases...
*/
void	expand_variable_heredoc( char **envp, char **token)
{
	t_env	*env;
	char	*expanded_token;

	env = ft_collector(sizeof(t_env), ALLOC);
	expanded_token = ft_strdup("");
	while (**token)
	{
		if ((**token == '$' && !is_digit_(*(*token + 1)) && is_alnum_(*(*token + 1)) == true))
		{
			extract_variable_name(*token + 1, env);
			get_env_value(envp, env);
			expanded_token = ft_strnjoin(expanded_token, env->value, env->value_len);
			*token = ft_trim(*token, env->name_len + 1);
		}
		else
		{
			expanded_token = ft_strnjoin(expanded_token, *token, 1);
			*token = ft_trim(*token, 1);
		}
	}
	*token = expanded_token;
}
