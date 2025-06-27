/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:22:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/27 22:47:49 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * echo is a builtin function (simple), we can use printf(),
 * but we prefer using write() function to manupulate file descriptors if we use pipes
 * -- 27-06-25 -- echo looks fine no errors or bugs!
 */
int	do_echo(t_cmd *data)
{
	char	**ptr;
	int		i;
	int		j;
	int		fd;
	int		is_newline;

	i = 0;
	fd = 1;
	is_newline = 1;
	ptr = ++data->argv;
	while (ptr[i][0] == '-' && ptr[i][1] == 'n')
	{
		j = 2;
		while (ptr[i][j] == 'n')
			j++;
		if (ptr[i][j] == '\0')
		{
			i++;
			is_newline = 0;
		}
		else
			break ;
	}
	if (*ptr)
	{
		while (ptr[i])
		{
			write(fd, ptr[i], ft_strlen(ptr[i]));
			if (ptr[i + 1])
				write(fd, " ", 1);
			i++;
		}
	}
	if (is_newline)
		write(fd, "\n", 1);
	return (1);
}
