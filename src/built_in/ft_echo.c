/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:22:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/21 00:57:51 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * echo is a builtin function (simple), we can use printf,
 * but we prefer using write function to manupulate file descriptors if we use pipes
 */
int	do_echo(t_cmd *data)
{
	char	**ptr;
	int		i;
	int		fd;
	int		is_newline;

	i = 0;
	fd = 1;
	is_newline = 1;
	ptr = ++data->argv;
	if (*ptr)
	{
		if (ptr[0][0] == '-' && ptr[0][1] == 'n')
		{
			i++;
			is_newline = 0;
		}
		while (ptr[i])
		{
			write(fd, ptr[i], ft_strlen(ptr[i]));
			write(fd, " ", 1);
			i++;
		}
	}
	if (is_newline)
		write(fd, "\n", 1);
	return (1);
}
