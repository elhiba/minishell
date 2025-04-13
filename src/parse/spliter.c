/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:42:44 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/12 16:01:47 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

char	*ft_remove_tabs(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '\t' || args[i] == '\n')
			args[i] = ' ';
		i++;
	}
	return (args);
}

char	**ft_spliter(char *args)
{
	char	**split;

	ft_remove_tabs(args);
	split = ft_split(args, ' ');
	if (!split)
		error_handler("Split");
	return (split);
}
