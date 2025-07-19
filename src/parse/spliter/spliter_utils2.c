/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 21:01:03 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/19 22:18:50 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_redirect(t_token *current, char *arg)
{
	int	i;

	i = 0;
	if (current->is_dquote || current->is_squote)
		return (0);
	if (arg[i] == '>' && arg[i + 1] == '>')
		return (1);
	else if (arg[i] == '>')
		return (1);
	else if (arg[i] == '<')
		return (1);
	return (0);
}

void	an_ambiguous(t_token **next)
{
	t_token	*tmp;

	build_error_name(*next);
	tmp = *next;
	while (tmp)
	{
		tmp->is_ambiguous = 1;
		if (tmp->is_space_next)
			break ;
		tmp = tmp->next;
	}
}

void	set_ambiguous(t_token *token, t_data *data)
{
	t_token	*current;
	t_token	*next;

	current = token;
	next = current->next;
	while (current)
	{
		if (is_redirect(current, current->arg)
			&& !current->next->is_not_splittable)
		{
			next = current->next;
			if (!next->is_dquote && (!ft_strcmp(next->arg, "")
					|| all_spaces(next->arg))
				&& (!next->next || (next->is_space_next)))
				next->is_ambiguous = 1;
			if (joining_result(next, data) > 1)
				next->is_ambiguous = 1;
			if (additional_check(next))
				next->is_ambiguous = 1;
			if (next && next->is_ambiguous)
				an_ambiguous(&next);
		}
		current = current->next;
	}
}
