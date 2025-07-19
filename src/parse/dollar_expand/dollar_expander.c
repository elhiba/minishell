/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:47:04 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/19 11:43:10 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	is_alnum_(char c)
{
	if ((ft_isalpha(c) || ft_isdigit(c)
			|| c == '_') && c != '$' && c != '\0')
		return (true);
	return (false);
}

bool	is_white_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

int	check_is_expandable(t_token *current)
{
	int		i;
	char	*buffer;

	i = 0;
	buffer = current->arg;
	while (buffer[i])
	{
		if ((buffer[i] == '$' && !ft_isdigit(buffer[i + 1]) \
			&& !is_white_space(buffer[i + 1])))
			return (1);
		i++;
	}
	return (0);
}

/*
	A function that will trim a substring from 
	the start of a string */
char	*ft_trim(char *str, int len)
{
	int		i;
	char	*trimmed_str;

	i = 0;
	trimmed_str = ft_collector(sizeof(char) * \
						(ft_strlen(str) - len + 1), ALLOC);
	while (str[i + len])
	{
		trimmed_str[i] = str[i + len];
		i++;
	}
	trimmed_str[i] = '\0';
	return (trimmed_str);
}

char	*dollar_handler(char *str, int *i)
{
	char	*arg;
	int		start;

	start = *i;
	++(*i);
	while ((str[*i] && ft_isalnum(str[*i]) && str[*i] != '\"' \
		&& str[*i] != '\'') || str[*i] == '_')
		(*i)++;
	arg = ft_substr(str, start, (*i - start));
	return (arg);
}
