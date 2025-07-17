/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:24:56 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/17 17:56:33 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * A normal exit should exit with 0
 * if exit with a number for ex : exit 2 should exit with 2
 * if exit with many args should print it as exit: too many arguments and 
 *	set status_exit with 1
 * There is an issue with exit codes !!!!here!!!!!!!!!!!1
 * !!!!!!!!!!!! STILL NOT FULL COMPLITED !!!!!!!!!!!!!!
 * */

void	is_numeric_arg(char **args, int *index)
{
	while (*index < (int)ft_strlen(args[0]))
	{
		if (ft_isalpha(args[0][*index]))
		{
			write(2, "minishell: exit: ", 17);
			write(2, args[0], ft_strlen(args[0]));
			write(2, ": numeric argument required\n", 28);
			exit(2);
		}
		(*index)++;
	}
}

int	do_exit(t_cmd *data)
{
	char	**args;
	int		i;

	i = 0;
	args = ++data->argv;
	write(1, "exit\n", 5);
	close(data->data->STDIN);
	close(data->data->STDOUT);
	if (*args)
	{
		if (args[0] != NULL)
		{
			is_numeric_arg(args, &i);
			if ((args[1]))
			{
				write(2, "minishell: exit: too many arguments\n", 36);
				data->data->last_exit_code = 1;
			}
			else
			{
				ft_collector(0, FREE);
				exit(ft_atoi(args[0]));
			}
		}
	}
	else
	{
		ft_collector(0, FREE);
		exit(0);
	}
	return (1);
}
