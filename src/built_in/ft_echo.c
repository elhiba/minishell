/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:22:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/15 16:37:06 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * echo is a builtin function (simple), we can use printf(),
 * but we prefer using write() function to manupulate file descriptors
 * if we use pipes
 * -- 27-06-25 -- echo looks fine no errors or bugs!
 */

void	allow_newline(char **arg, int *index, int *is_newline)
{
	int	j;

	j = 0;
	while (arg[*index][0] == '-' && arg[*index][1] == 'n')
	{
		j = 2;
		while (arg[*index][j] == 'n')
			j++;
		if (arg[*index][j] == '\0')
		{
			(*index)++;
			*is_newline = 0;
		}
		else
			break ;
	}
}

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
		allow_newline(ptr, &i, &is_newline);
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
	data->data->last_exit_code = 0;
	return (1);
}
