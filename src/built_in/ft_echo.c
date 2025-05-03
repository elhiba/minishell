/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:22:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/29 16:44:05 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * updated list name
 */
int	do_echo(t_data *data)
{
	t_token	*cd_args;
	int		is_n;

	is_n = 0;
	cd_args = data->token_list->next;
	if (!cd_args)
		return (printf("\n"), 1);
	else if (ft_strcmp(cd_args->arg, "-n") == 0)
	{
		is_n = 1;
		cd_args = cd_args->next;
	}
	while (cd_args)
	{
		printf("%s", cd_args->arg);
		if (cd_args->next)
			printf(" ");
		cd_args = cd_args->next;
	}
	if (!is_n)
		printf("\n");
	data->last_exit_code = 0;
	return (1);
}
