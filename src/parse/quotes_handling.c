/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:02:58 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/27 17:34:39 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/history.h>

//void	double_quotes(t_data *data, int index)
//{
//	if (!data->is_dquote)
//	{
//		data->is_dquote = 1;
//		if (data->readline_in)
//			data->readline_in[index] = ' ';
//	}
//	else if (data->is_dquote)
//	{
//		data->readline_in[index] = ' ';
//		data->is_dquote = 0;
//	}
//
//}
//
//void	signle_quotes(t_data *data, int index)
//{
//	if (!data->is_squote)
//	{
//		data->is_squote = 1;
//		if (data->readline_in)
//			data->readline_in[index] = ' ';
//	}
//	else
//	{
//		data->readline_in[index] = ' ';
//		data->is_squote = 0;
//	}
//}
//
//void	quotes_handler(t_data *data)
//{
//	int	i;
//
//	i = 0;
//
//	while (data->readline_in[i])
//	{
//		if (data->readline_in[i] == '\"'&& !data->is_squote)
//			double_quotes(data, i);
//		if (data->readline_in[i] == '\'' && !data->is_dquote)
//			signle_quotes(data, i);
//		i++;
//	}
//}
//
//void	single_quote(t_token *node)
//{
//
//}

char	*quotes_handler(char *str, int *index, int *flag)
{
	char	*arg;
	int		start;
	int		is_dquote;
	int		is_squote;

	(1) && (is_dquote = 0, is_squote = 0);
	if (str[*index] == '\"')
		(1) && (is_dquote = 1, *flag = DOUBLE_QUOTE);
	else
		(1) && (is_squote = 1, *flag = SINGLE_QUOTE);
	start = *index + 1;
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
	arg = ft_substr(str, start, *index - start);
	return ((*index)++, arg);
}
