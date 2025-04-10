/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:22:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/10 12:12:53 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * It hard coded lol!, but it works as we expected it to do!
 */
int	do_echo(t_token *input)
{
	t_token	*ptr;

	ptr = input->next;

	if (ft_strcmp(ptr->arg, "-n") == 0)
	{
		ptr = ptr->next;
		while (ptr)
		{
			printf("%s", ptr->arg);
			if (ptr->next)
				printf(" ");
			ptr = ptr->next;
		}
	}
	else if (ptr->arg)
	{
		while (ptr)
		{
			printf("%s", ptr->arg);
			if (ptr->next)
				printf(" ");
			ptr = ptr->next;
		}
		printf("\n");
	}
	else if ((!input->arg))
		printf("\n");
	return (0);
}
