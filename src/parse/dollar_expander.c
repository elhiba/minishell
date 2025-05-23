/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:04 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/20 11:35:50 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	free_ptr(char	*ptr)
{
	free(ptr);
	ptr = NULL;
}

char	*expander(t_data *data, char *env, char *ptr)
{
	char	*tenv;
	char	*dup;
	char	*substr;

	++env;
	tenv = ft_getenv(env, data);
	if (*env == '?')
		return (free(ptr), ft_itoa(data->last_exit_code));
	if (ptr[0] != '$')
	{
		if (!tenv)
		{
			free(tenv);
			tenv = ft_substr(ptr, 0, (ft_strlen(ptr) - ft_strlen(env)) - 1);
			free_ptr(ptr);
			return (tenv);
		}
		dup = ft_strdup(tenv);
		substr = ft_substr(ptr, 0, (ft_strlen(ptr) - ft_strlen(env)) - 1);
		tenv = ft_strjoin(substr, dup);
		free_ptr(ptr);
		free_ptr(dup);
		free_ptr(substr);
		return (tenv);
	}
	if (tenv)
		return (free_ptr(ptr), strdup(tenv));
	return (free_ptr(ptr), strdup("\0"));
}

void	dollar_expand(t_data *data, t_token *token)
{
	t_token	*ptr;
	char	*env;

	ptr = token;
	while (ptr)
	{
		if ((env = ft_strchr(ptr->arg, '$')))
			ptr->arg = expander(data, env, ptr->arg);
		ptr = ptr->next;
	}
}
