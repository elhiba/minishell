/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:24:56 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/14 16:37:03 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * A normal exit should exit with 0
 * if exit with a number for ex : exit 2 should exit with 2
 * if exit with many args should print it as exit: too many arguments and set status_exit with 1
 * There is an issue with exit codes !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!here!!!!!!!!!!!1
 * !!!!!!!!!!!! STILL NOT FULL COMPLITED !!!!!!!!!!!!!!
 * */

int	do_exit(t_cmd *data)
{
	char	**args;

	args = ++data->argv;

	write(1, "exit\n", 5);
	if (*args)
	{
		if (args[1] != NULL)
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			data->data->last_exit_code = 1;
		}
		else
			exit(ft_atoi(args[0]));
	}
	else
		exit(0);
	return (1);
}
