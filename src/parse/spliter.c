/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:42:44 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/05 17:22:41 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		operation_len(char *str)
{
	if (str[0] == '>' && str[1] == '>')
		return (2);
	if (str[0] == '<' && str[1] == '<')
		return (2);
	if (str[0] == '|' || str[0] == '<' || str[0] == '>')
		return (1);
	return (0);
}

int		arg_counter(char *str)
{

	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (operation_len(str + i))
		{
			count++;
			i += operation_len(str + i);
		}
		else
		{
			count++;
			while (str[i] && str[i] != ' ' && !operation_len(str + i))
				i++;
		}
	}
	return (count);

}

char	**ft_spliter(t_data *data)
{
	char	**args;
	int		op_len;
	int		index;
	int		i;
	int		start;

	i = 0;
	index = 0;
	args = (char **)malloc(sizeof(char *) * (arg_counter(data->readline_in) + 1));
	while (data->readline_in[i])
	{
		if (data->readline_in[i] == ' ')
			i++;
		if (!data->readline_in[i])
			break ;
		op_len = operation_len(data->readline_in + i);
		if (op_len)
		{
			args[index] = ft_substr(data->readline_in, i, op_len);
			index++;
			i += op_len;
		}
		else
		{
			start = i;
			while (data->readline_in[i] && !(data->readline_in[i] == ' ') && !operation_len(data->readline_in + i))
				i++;
			args[index] = ft_substr(data->readline_in, start, i - start);
			index++;
		}
	}
	args[index] = NULL;
	return (args);
}
