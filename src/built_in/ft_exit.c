/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:24:56 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/01 19:09:25 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_strict_num(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (str[0] == '+' || str[0] == '-')
		str++;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (i > 0);
}

static int	parse_exit_code(char *str, long long *result)
{
	int			sign;
	long long	num;

	sign = 1;
	num = 0;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		num = num * 10 + (*str - '0');
		if ((sign == 1 && num > LLONG_MAX) || (sign == -1 && -num < LLONG_MIN))
			return (0);
		str++;
	}
	*result = num * sign;
	return (1);
}

int	do_exit(t_data *data, t_token *list)
{
	t_token		*arg;
	long long	exit_status;

	printf("exit\n");
	arg = list->next;
	if (arg)
	{
		if (!is_strict_num(arg->arg)
			|| !parse_exit_code(arg->arg, &exit_status))
		{
			printf("exit: %s: numeric argument required\n", arg->arg);
			full_cleanup(data);
			exit(2);
		}
		if (arg->next)
			return (printf("exit: too many arguments\n"),
				data->last_exit_code = 1, 1);
	}
	else
		exit_status = data->last_exit_code;
	full_cleanup(data);
	exit((unsigned char)exit_status);
	return (1);
}
