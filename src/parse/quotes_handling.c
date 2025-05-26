/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:02:58 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/26 23:38:39 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

//void	double_quotes(t_data *data, int index)
//{
//	if (!data->is_dquote)
//	{
//		data->is_dquote = 1;
//		if (data->readline_in)
//			data->readline_in[index] = ' ';
//	}
//	else if (data->is_dquote)
//	{
//		data->readline_in[index] = ' ';
//		data->is_dquote = 0;
//	}
//
//}
//
//void	signle_quotes(t_data *data, int index)
//{
//	if (!data->is_squote)
//	{
//		data->is_squote = 1;
//		if (data->readline_in)
//			data->readline_in[index] = ' ';
//	}
//	else
//	{
//		data->readline_in[index] = ' ';
//		data->is_squote = 0;
//	}
//}
//
//void	quotes_handler(t_data *data)
//{
//	int	i;
//
//	i = 0;
//
//	while (data->readline_in[i])
//	{
//		if (data->readline_in[i] == '\"'&& !data->is_squote)
//			double_quotes(data, i);
//		if (data->readline_in[i] == '\'' && !data->is_dquote)
//			signle_quotes(data, i);
//		i++;
//	}
//}
//
//void	single_quote(t_token *node)
//{
//
//}

void	double_quote(t_token *node)
{
	t_token	*head_node;
	t_token	*last_node;
	char	*full_arg;

	head_node = node;
	while (node)
	{
		full_arg = ft_strjoin(full_arg, node->arg);
		if (!full_arg)
			error_handler("ft_strjoin", NULL);
		last_node = node;
		node = node->next;
	}
	free(head_node->arg);
	head_node->arg = NULL;
	head_node->arg = full_arg;
	if (last_node->next)
		head_node->next = last_node;
	else
		head_node->next = NULL;
}

void	quotes_handler(t_token **head)
{
	t_token	*ptr;

	ptr = *head;
	while (ptr)
	{
		if (ft_strchr(ptr->arg, '\"'))
			double_quote(ptr);
//		else if (ft_strchr(ptr->arg, '\''))
//			single_quote(ptr);
		ptr = ptr->next;
	}
}
