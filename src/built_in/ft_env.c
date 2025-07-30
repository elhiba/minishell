/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:46:17 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/30 13:56:39 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * This is probably a complete function! Still no updates (looks fine)
 */

int	do_env(t_cmd *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = 1;
	while (data->data->env[i])
	{
		if (ft_strchr(data->data->env[i], '='))
		{
			write(fd, ft_strjoin(data->data->env[i], "\n"),
				ft_strlen(data->data->env[i]));
		}
		i++;
	}
	data->data->last_exit_code = 0;
	return (1);
}
