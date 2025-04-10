/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:51:50 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/10 11:17:49 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_node(char *arg)
{
	t_token	*node;

	node = malloc(sizeof(t_token));

	node->arg = ft_strdup(arg);
	node->next = NULL;
	node->prev = NULL;

	return (node);
}

void	add_list(t_token **head, t_token *node)
{
	t_token	*ptr;

	ptr = *head;
	if (!node)
		return ;

	else if (!*head)
		*head = node;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = node;
	}
}
