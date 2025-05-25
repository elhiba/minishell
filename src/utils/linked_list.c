/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:51:50 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/25 00:42:55 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_token_node(t_token **head, char *arg)
{
	t_token	*new;
	t_token	*curr;

	if (!arg)
		return ;
	new = malloc(sizeof(t_token));
	if (!new)
		error_handler("malloc", NULL);
	ft_bzero(new, sizeof(t_token));
	new->arg = arg;
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
