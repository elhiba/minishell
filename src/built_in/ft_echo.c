/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:22:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/16 10:27:46 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

/*
 * It hard coded lol!, but it works as we expected it to do!
 */
int	do_echo(t_token *tok_list)
{
	t_token	*ptr;
	int		is_n;

	is_n = 0;
	ptr = tok_list->next;
	if (!ptr)
		printf("\n");
	else if (ft_strcmp(ptr->arg, "-n") == 0)
	{
		is_n = 1;
		ptr = ptr->next;
	}
	while (ptr)
	{
		printf("%s", ptr->arg);
		if (ptr->next)
			printf(" ");
		ptr = ptr->next;
	}
	if (!is_n)
		printf("\n");
	return (1);
}
