/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:02:58 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/25 18:03:22 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	double_quotes(t_data *data, int index)
{
	if (!data->is_dquote)
	{
		data->is_dquote = 1;
		if (data->readline_in)
			data->readline_in[index] = ' ';
	}
	else if (data->is_dquote)
	{
		data->readline_in[index] = ' ';
		data->is_dquote = 0;
	}

}

void	signle_quotes(t_data *data, int index)
{
	if (!data->is_squote)
	{
		data->is_squote = 1;
		if (data->readline_in)
			data->readline_in[index] = ' ';
	}
	else
	{
		data->readline_in[index] = ' ';
		data->is_squote = 0;
	}
}

void	quotes_handler(t_data *data)
{
	int	i;

	i = 0;

	while (data->readline_in[i])
	{
		if (data->readline_in[i] == '\"'&& !data->is_squote)
			double_quotes(data, i);
		if (data->readline_in[i] == '\'' && !data->is_dquote)
			signle_quotes(data, i);
		i++;
	}
}
