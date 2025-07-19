/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:04:23 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/20 00:42:14 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	there_is_ambiguous(t_token **head, t_token *save, t_token **tmp, \
				char **buffer)
{
	add_token_node(head, ft_strdup(""));
	*buffer += ft_strlen(*buffer);
	*tmp = *head;
	while ((*tmp)->next)
		(*tmp) = (*tmp)->next;
	(*tmp)->is_word = 1;
	(*tmp)->is_env_var = 1;
	(*tmp)->is_space_next = 1;
	if (save && !save->prev && !save->is_space_next)
		(*tmp)->is_space_next = 0;
	if (save && save->is_ambiguous)
	{
		(*tmp)->ambiguous_name = save->ambiguous_name;
		(*tmp)->is_ambiguous = 1;
	}
}

void	split_into_nodes(t_token **head, t_token *save, char *buffer)
{
	t_token	*tmp;
	int		first_index_flag;
	int		space_flag;

	first_index_flag = 0;
	space_flag = 0;
	while (*buffer)
	{
		if (*head && !first_index_flag && is_space(*buffer) \
			&& !all_spaces(buffer))
		{
			(*head)->is_space_next = 1;
			first_index_flag = 1;
		}
		if (!space_flag && all_spaces(buffer))
			there_is_ambiguous(head, save, &tmp, &buffer);
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

void	split_job(t_token **token, bool *prev_was_null, void **boat)
{
	t_token	**prev;
	t_token	**current;
	t_token	**next;
	t_token	**save;

	(1) && (prev = boat[0], current = boat[1]);
	(1) && (next = boat[2], save = boat[3]);
	if (*prev)
	{
		*save = (*prev)->next;
		(*prev)->next = NULL;
		*prev_was_null = false;
	}
	else
		*save = *current;
	split_into_nodes(&*prev, *save, (*current)->arg);
	if (*prev_was_null)
		*token = *prev;
	while ((*prev)->next)
		*prev = (*prev)->next;
	if (*save && (*save)->is_space_next)
		(*prev)->is_space_next = 1;
	(*prev)->next = *next;
	if (*next)
		(*next)->prev = *prev;
}

void	split_expanded(t_token **token, t_data *data, void **boat)
{
	t_token	*prev;
	t_token	*current;
	t_token	*next;
	t_token	*save;
	bool	prev_was_null;

	(void)data;
	boat = ft_collector(sizeof(void *) * 5, ALLOC);
	current = *token;
	prev_was_null = true;
	save = NULL;
	boat[1] = &current;
	boat[3] = &save;
	while (current)
	{
		next = current->next;
		prev = current->prev;
		boat[0] = &prev;
		boat[2] = &next;
		if (current->is_env_var && !current->is_not_splittable
			&& !current->is_dquote && !current->is_squote
			&& there_is_space(current->arg) && current->is_dquote != 1)
			split_job(token, &prev_was_null, boat);
		current = current->next;
	}
}
