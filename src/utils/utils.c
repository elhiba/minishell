/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:23:14 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/10 15:47:23 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

// shitySplit function!
char **ft_splits(char *arg, char *delimits)
{
	int		i;
	int		len;
	char	**args;

	i = 0;
	len = ft_strlen(delimits);

	while (i < len)
	{
		args = ft_split(arg, delimits[i]);
		if (!args)
			break;
		i++;
	}
	return (args);
}
