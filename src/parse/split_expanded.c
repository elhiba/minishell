/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:04:23 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/01 21:59:42 by moel-hib         ###   ########.fr       */
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

void	extract_word(char **buffer, t_token **head, t_token *save)
{
	char	*token;
	int		len;
	t_token	*tmp;

	len = 0;
	while ((*buffer)[len] != '\0' && !is_space((*buffer)[len]))
		len++;
	token = ft_strndup(*buffer, len);
	*(buffer) += len;
	add_token_node(head, token);
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->is_squote = 1;
	if (save && save->is_ambiguous)
	{
		tmp->is_ambiguous = 1;
		tmp->ambiguous_name = save->ambiguous_name;
	}
	if (is_space(**buffer))
		tmp->is_space_next = 1;
}

int	all_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!is_space(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	split_into_nodes(t_token **head, t_token *save, char *buffer)
{
	t_token	*tmp;
	int		first_index_flag;
	int		space_flag;

	first_index_flag  = 0;
	space_flag = 0;
	while (*buffer)
	{
		if (*head && !first_index_flag && is_space(*buffer) && !all_spaces(buffer))
		{
			(*head)->is_space_next = 1;
			first_index_flag = 1;
		}
		if (!space_flag && all_spaces(buffer))
		{
			add_token_node(head, ft_strdup(""));
			buffer += ft_strlen(buffer);
			tmp = *head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->is_word = 1;
			tmp->is_env_var = 1;
			tmp->is_space_next = 1;
			if (save && !save->is_space_next)
				tmp->is_space_next = 0;
			if (save && save->is_ambiguous)
			{
				tmp->ambiguous_name = save->ambiguous_name;
				tmp->is_ambiguous = 1;
			}
		}
		else if (is_space(*buffer))
			buffer++;
		else
		{
			extract_word(&buffer, head, save);
			space_flag = 1;
			first_index_flag = 1;
		}
	}
}

void	split_expanded(t_token **token, t_data *data)
{
	t_token	*prev;
	t_token	*current;
	t_token	*next;
	t_token	*save;
	bool	prev_was_null;

	(void)data;
	current = *token; 
	prev_was_null = true;
	save = NULL;
	while (current)
	{
		next = current->next;
		prev = current->prev;
		if (current->is_env_var && !current->is_not_splittable && !current->is_dquote && !current->is_squote && there_is_space(current->arg) && current->is_dquote != 1)
		{
			if (prev)
			{
				save = prev->next;
				prev->next = NULL;
				prev_was_null = false;
			}
			else
				save = current;
			split_into_nodes(&prev, save, current->arg);
			if (prev_was_null)
				*token = prev;
			while (prev->next)
				prev = prev->next;
			if (save && save->is_space_next)
				prev->is_space_next = 1;
			prev->next = next;
			if (next)
				next->prev = prev;
		}
		current = current->next;
	}
}
