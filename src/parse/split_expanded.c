/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:04:23 by slasfar           #+#    #+#             */
/*   Updated: 2025/05/30 16:17:43 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

int	there_is_space(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
			return (1);
		i++;
	}
	return (0);
}

void	extract_word(char **buffer, t_token **head)
{
	char	*token;
	int		len;
	t_token	*tmp;

	len = 0;
	tmp = *head;
	while ((*buffer)[len] != '\0' && !is_space((*buffer)[len]))
		len++;
	token = ft_strndup(*buffer, len);
	*(buffer) += len;
	add_token_node(head, token);
	while (tmp->next)
		tmp = tmp->next;
	tmp->is_squote = 1;
}

void	split_into_nodes(t_token **head, char *buffer)
{
	while (*buffer)
	{
		if (is_space(*buffer))
			buffer++;
		else
			extract_word(&buffer, head);
	}
}


void	split_expanded(t_token **token, t_data *data)
{
	t_token	*prev;
	t_token	*current;
	t_token	*next;
	bool	prev_was_null;

	current = *token; 
	prev_was_null = true;
	while (current)
	{
		next = current->next;
		prev = current->prev; // NULL
		if (current->is_env_var && there_is_space(current->arg) && current->is_dquote != 1)
		{
			if (prev)
				(1) && (prev->next = NULL, prev_was_null = false);
			split_into_nodes(&prev, current->arg);
			if (prev_was_null)
				*token = prev;
			while (prev->next)
				prev = prev->next;
			prev->next = next;
		}
		current = current->next;
	}
}
