/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:46:17 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/20 22:57:06 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * this is probably a complete function!
 */
int	do_env(t_cmd *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = 1;
	while (data->data->env[i])
	{
		write(fd, data->data->env[i], ft_strlen(data->data->env[i]));
		write(fd, "\n", 1);
		i++;
	}
	return (1);
}
