/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:02:58 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/20 00:04:02 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	is_quote_handler(int is_dquote, int is_squote, char *str, int *index)
{
	while (is_dquote)
	{
		if (str[*index + 1] == '\"')
			is_dquote = 0;
		(*index)++;
	}
	while (is_squote)
	{
		if (str[*index + 1] == '\'')
			is_squote = 0;
		(*index)++;
	}
}

char	*quotes_handler(char *str, int *index, int *flag)
{
	char	*arg;
	int		start;
	int		is_dquote;
	int		is_squote;

	(1) && (is_dquote = 0, is_squote = 0);
	if (str[*index] == '\"')
	{
		is_dquote = 1;
		*flag = 10;
	}
	else
	{
		is_squote = 1;
		*flag = 11;
	}
	start = *index + 1;
	is_quote_handler(is_dquote, is_squote, str, index);
	arg = ft_substr(str, start, *index - start);
	return ((*index)++, arg);
}
