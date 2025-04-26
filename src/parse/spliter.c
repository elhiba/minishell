/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:42:44 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/23 18:32:26 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		error_handler("Split", NULL);
	return (split);
}
