/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:06:51 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/19 09:29:03 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_it_expandable(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if ((buffer[i] == '$' && !ft_isdigit(buffer[i + 1]) \
			&& !is_white_space(buffer[i + 1])))
			return (1);
		i++;
	}
	return (0);
}

/*
	this function is the same as the normal expanding function, just without all the eadge cases...
*/
void	expand_variable_heredoc(t_data *data, char **envp, char **token)
{
	t_env	*env;
	char	*expanded_token;
	char	*exit_code;

	exit_code = ft_itoa(data->last_exit_code);
	env = ft_collector(sizeof(t_env), ALLOC);
	expanded_token = ft_strdup("");	
	while (**token)
	{
		if (**token == '$' && *(*token + 1) == '?')
		{
			expanded_token = ft_strnjoin(expanded_token, exit_code, ft_strlen(exit_code));
			*token = ft_trim(*token, 2);
		}
		else if ((**token == '$' && !ft_isdigit(*(*token + 1)) && is_alnum_(*(*token + 1)) == true))
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
