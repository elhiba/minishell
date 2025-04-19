/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:23:14 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/19 10:22:58 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token_list(t_token **head)
{
	t_token	*tmp;
	t_token	*next;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->arg)
			free(tmp->arg);
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}

void	free_d_arr(char **arr)
{
	char **ptr;
	int	i;

	ptr = arr;
	i = 0;
	while (arr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

// shitySplit function!
char **ft_splits(char *arg, char *delimits)
{
	int		i;
	int		len;
	char	**args;

	i = 0;
	len = ft_strlen(delimits);

	while (i < len)
	{
		args = ft_split(arg, delimits[i]);
		if (!args)
			break;
		i++;
	}
	return (args);
}
