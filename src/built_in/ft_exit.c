/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:24:56 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/30 14:12:33 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * A normal exit should exit with 0
 * if exit with a number for ex : exit 2 should exit with 2
 * if exit with many args should print it as exit: too many arguments and 
 *	set status_exit with 1
* */
void	is_numeric_arg(char **args, int *index)
{
	while (*index < (int)ft_strlen(args[0]))
	{
		if (ft_isalpha(args[0][*index]))
		{
			write(2,
				ft_strjoin3("minishell: exit: ", args[0], \
				": numeric argument required\n"), ft_strlen(args[0]) + 45);
			ft_collector(0, FREE);
			exit(2);
		}
		(*index)++;
	}
}

void	exit_errors(char **args, int *i, t_cmd **data)
{
	int	exit_code;

	if (args[0] != NULL)
	{
		exit_code = ft_atoi(args[0]);
		is_numeric_arg(args, i);
		if ((args[1]))
		{
			write(2, "minishell: exit: too many arguments\n", 36);
			(*data)->data->last_exit_code = 1;
		}
		else
		{
			ft_collector(0, FREE);
			exit(exit_code);
		}
	}
}

int	do_exit(t_cmd *data)
{
	char	**args;
	int		i;

	i = 0;
	args = ++data->argv;
	write(2, "exit\n", 5);
	(1) && (close(data->data->stdin_), close(data->data->stdout_));
	if (*args)
		exit_errors(args, &i, &data);
	else
	{
		ft_collector(0, FREE);
		exit(0);
	}
	return (1);
}
