/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 00:42:31 by slasfar           #+#    #+#             */
/*   Updated: 2025/05/31 18:13:25 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = ft_collector((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char), ALLOC);
	if (!str)
		return (ft_collector(0, EXIT));
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i++] = s2[j];
		j++;
	}
	str[i] = '\0';
	return (str);
}

void	join_tokens(t_token **tokens)
{
	t_token	*current;
	t_token *save_next;

	current = *tokens;
	save_next = current->next;
	while (save_next)
	{
		if (!current->is_space_next)
		{
			current->arg = ft_strjoin_(current->arg, save_next->arg);
			current->next = save_next->next;
			if (save_next->next)
				save_next->next->prev = current;
			if (save_next->is_space_next)
				current->is_space_next = 1;
			if (current->is_env_var || save_next->is_env_var)
				current->is_env_var = 1;
			current->is_squote = 1;
		}
		else
			current = save_next;
		save_next = current->next;
	}
}
