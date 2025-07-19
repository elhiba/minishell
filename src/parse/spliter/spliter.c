/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:42:44 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/20 00:43:02 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	operator_cleaner(char *arg)
{
	if (arg[0] == '>' && arg[1] == '>' && arg[2] == '\0')
		return (2);
	if (arg[0] == '<' && arg[1] == '<' && arg[2] == '\0')
		return (2);
	if ((arg[0] == '<' || arg[0] == '>') && arg[1] == '\0')
		return (1);
	return (0);
}

void	node_cleaner(t_token **head)
{
	t_token	*ptr;

	ptr = *head;
	while (ptr)
	{
		if ((!ptr->is_squote &&!ptr->is_dquote && !ptr->is_env_var)
			&& operator_cleaner(ptr->arg))
		{
			if (!ptr->prev)
			{
				*head = ptr->next;
				(*head)->prev = NULL;
			}
			ptr = ptr->next;
			if (ptr->prev)
			{
				ptr->prev = ptr->prev;
				ptr->prev->prev->next = ptr;
			}
		}
		ptr = ptr->next;
	}
}

void	remove_empty_env(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		if (!current->prev && current->is_env_var
			&& ft_strcmp(current->arg, "") == 0 && !current->is_dquote)
		{
			*head = current->next;
			if (current->next)
				current->next->prev = *head;
		}
		else if (current->is_env_var
			&& ft_strcmp(current->arg, "") == 0 && !current->is_dquote)
		{
			current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
		}
		current = current->next;
	}
}

t_token	*token(char *str, t_data *data)
{
	t_token	*tok;
	t_token	*ptr;

	tok = NULL;
	ft_spliter(&tok, str, data);
	split_expanded(&tok, data, NULL);
	join_tokens(&tok);
	ptr = tok;
	while (ptr)
	{
		typer(&ptr, ptr->arg);
		ptr = ptr->next;
	}
	node_cleaner(&tok);
	return (tok);
}

void	**ft_tokenizer(t_data *data)
{
	void	**tok;
	char	**ptok;
	int		i;

	i = 0;
	ptok = special_split(data->readline_in, '|');
	if (!ptok)
		error_handler("pipe split", data);
	while (ptok[i])
		i++;
	tok = ft_collector(sizeof(void *) * (i + 1), ALLOC);
	if (!tok)
		ft_collector(0, EXIT);
	i = 0;
	while (ptok[i])
	{
		tok[i] = token(ptok[i], data);
		if (!tok[i])
			return (NULL);
		i++;
	}
	tok[i] = NULL;
	return (tok);
}
