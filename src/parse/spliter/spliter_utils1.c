/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:09:53 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/20 00:43:26 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	add_tmp(t_token **head, t_token *new)
{
	t_token	*curr;

	if (!*head)
		*head = new;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
		new->prev = curr;
	}
}

void	cp_flag(t_token *dest, t_token *src)
{
	dest->is_dquote = src->is_dquote;
	dest->is_env_var = src->is_env_var;
	dest->is_squote = src->is_squote;
	dest->is_word = src->is_word;
	dest->is_space_next = src->is_space_next;
	dest->is_not_splittable = src->is_not_splittable;
	dest->is_heredoc = src->is_heredoc;
	dest->is_append = src->is_append;
	dest->is_outfile = src->is_outfile;
	dest->is_infile = src->is_infile;
}

int	joining_result(t_token	*token, t_data *data)
{
	t_token	*tmp_list;
	t_token	*current;
	int		i;

	i = 0;
	tmp_list = NULL;
	while (token)
	{
		current = ft_collector(sizeof(t_token), ALLOC);
		current->arg = ft_strdup(token->arg);
		cp_flag(current, token);
		add_tmp(&tmp_list, current);
		if (token->is_space_next)
			break ;
		token = token->next;
	}
	split_expanded(&tmp_list, data, NULL);
	join_tokens(&tmp_list);
	current = tmp_list;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

int	additional_check(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && !current->is_env_var)
		current = current->next;
	if (current->arg[0] && all_spaces(current->arg)
		&& (!current->prev->is_space_next && !current->is_space_next))
		return (1);
	return (0);
}

void	build_error_name(t_token *token)
{
	char	*error_name;
	t_token	*current;

	current = token;
	error_name = ft_strdup("");
	while (current)
	{
		if (current->is_env_var && current->is_word)
			error_name = ft_strjoin(error_name, current->key);
		else if (current->is_env_var && current->is_dquote)
			error_name = ft_strjoin(error_name,
					ft_strjoin("\"", ft_strjoin(current->key, "\"")));
		else if (current->is_word)
			error_name = ft_strjoin(error_name, current->arg);
		else if (current->is_dquote)
			error_name = ft_strjoin(error_name,
					ft_strjoin("\"", ft_strjoin(current->arg, "\"")));
		else if (current->is_squote)
			error_name = ft_strjoin(error_name,
					ft_strjoin("\'", ft_strjoin(current->arg, "\'")));
		if (current->is_space_next)
			break ;
		current = current->next;
	}
	token->ambiguous_name = error_name;
}
