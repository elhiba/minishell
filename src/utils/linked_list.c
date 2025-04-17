/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:51:50 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/17 22:19:51 by sel-maaq         ###   ########.fr       */
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
		error_handler("Malloc failed", NULL);
	new->arg = arg;
	new->next = NULL;
	new->prev = NULL;
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
