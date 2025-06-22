/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:23:14 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/26 16:59:10 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin3(const char *str1, const char *middle, const char *str2)
{
	char	*tmp;
	char	*full_result;

	tmp = ft_strjoin(str1, middle);
	full_result = ft_strjoin(tmp, str2);
	free(tmp);
	return (full_result);
}

char	**ft_splits(char *arg, char *delimits)
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
			break ;
		i++;
	}
	return (args);
}
