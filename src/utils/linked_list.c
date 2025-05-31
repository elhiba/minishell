/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:51:50 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/31 18:02:10 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_token_node(t_token **head, char *arg)
{
	t_token	*new;
	t_token	*curr;

	if (!arg)
		return ;
	new = ft_collector(sizeof(t_token), ALLOC);
	if (!new)
		ft_collector(0, EXIT);
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
