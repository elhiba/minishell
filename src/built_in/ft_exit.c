/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:24:56 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/20 17:41:05 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	only_num(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	do_exit(t_cmd *data)
{
//	int		arg_count;
//	int		exit_status;
//	t_token	*tmp;
//
//	tmp = data->token_list->next;
//	printf("exit\n");
//	arg_count = 0;
//	while (tmp)
//	{
//		arg_count++;
//		if (!only_num(tmp->arg) && arg_count == 1)
//		{
//			printf("exit: %s: numeric argument required\n", tmp->arg);
//			exit(2);
//		}
//		if (arg_count > 1)
//			return (printf("exit: too many arguments\n"), data->last_exit_code = 1, 1);
//		tmp = tmp->next;
//	}
//	if (arg_count == 0)
//		exit_status = data->last_exit_code;
//	else
//		exit_status = ft_atoi(data->token_list->next->arg);
//	exit(exit_status);
	return (1);
}
