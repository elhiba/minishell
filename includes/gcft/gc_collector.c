/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:03:06 by moel-hib          #+#    #+#             */
/*   Updated: 2025/08/02 16:14:37 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_collector.h"

/*
	Old way to add node that allocated
	-- IT WASTE TIME --
void	add_back(void **head, void *node)
{
	t_collector	*ptr;

	ptr = *head;
	if (!ptr)
		*head = node;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = node;
	}
}
*/

void	add_front(void **head, void *node)
{
	t_collector	*f_head;
	t_collector	*f_node;

	f_head = *head;
	f_node = node;
	if (!f_head)
		*head = node;
	else
	{
		*head = f_node;
		f_node->next = f_head;
	}
}

void	node_handler(void **head, t_collector *node, size_t size)
{
	node = malloc(sizeof(t_collector));
	ft_bzero(node, sizeof(t_collector));
	if (!node)
		ft_collector(0, EXIT);
	node->addr = malloc(size);
	ft_bzero(node->addr, size);
	if (!node->addr)
		ft_collector(0, EXIT);
	node->next = NULL;
	add_front(head, node);
}

void	free_head(void **head, int flag)
{
	t_collector	*node;
	t_collector	*ptr;

	ptr = *(t_collector **)head;
	while (ptr)
	{
		node = ptr->next;
		free(ptr->addr);
		free(ptr);
		ptr = node;
	}
	if (flag == EXIT)
		exit(0);
}

void	*ft_collector(size_t size, int flag)
{
	static void	*head = NULL;
	t_collector	*ptr;
	t_collector	*node;

	node = NULL;
	if (size <= 0 && flag == ALLOC)
		return (NULL);
	if (flag == ALLOC)
	{
		node_handler(&head, node, size);
		ptr = (t_collector *)head;
	}
	else if (flag == FREE || flag == EXIT)
		free_head(&head, flag);
	if (flag == FREE)
		return (NULL);
	else
		return (ptr->addr);
}
