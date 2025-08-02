/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:23:14 by moel-hib          #+#    #+#             */
/*   Updated: 2025/08/02 10:21:58 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin3(const char *str1, const char *middle, const char *str2)
{
	return (ft_strjoin(ft_strjoin(str1, middle)
			, str2));
}

char	*ft_strtrim(char *str, int limit)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_collector(sizeof(char) * (limit + 2), ALLOC);
	while (i <= limit)
	{
		result[i] = str[i];
		i++;
	}
	return (result);
}

int	ft_arglen(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

/* Search And Retrieve */
char	*sea_ret(char **env, char *arg)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(arg);
	while (env[i])
	{
		if (ft_strncmp(env[i], arg, len) == 0)
		{
			if (env[i][len] == '=')
				return (env[i] + (len + 1));
			else
				return (ft_strdup(""));
		}
		i++;
	}
	return (NULL);
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
