/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:10:02 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/19 12:10:52 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	check_quotes(char *str, int i, int *is_dquote, int *is_squote)
{
	if (str[i] == '\"' && !*is_dquote && !*is_squote)
		*is_dquote = 1;
	else if (str[i] == '\"' && *is_dquote && !*is_squote)
		*is_dquote = 0;
	if (str[i] == '\'' && !*is_squote && !*is_dquote)
		*is_squote = 1;
	else if (str[i] == '\'' && *is_squote && !*is_dquote)
		*is_squote = 0;
}

int	check_closed_quotes(int s_quote, int d_quote)
{
	if (d_quote)
	{
		printf("%s `\"'\n", SYN_Q_ERROR);
		return (2);
	}
	else if (s_quote)
	{
		printf("%s `\''\n", SYN_Q_ERROR);
		return (2);
	}
	return (0);
}

void	status_ret(t_data *data, int *status, int is_squote, int is_dquote)
{
	if (!*status)
		*status = check_closed_quotes(is_squote, is_dquote);
	if (*status)
		data->last_exit_code = *status;
}

int	syntax_checker(t_data *data)
{
	int		i;
	int		status;
	int		is_dquote;
	int		is_squote;

	(1) && (i = 0, status = 0, is_dquote = 0, is_squote = 0);
	while (data->readline_in[i])
	{
		check_quotes(data->readline_in, i, &is_dquote, &is_squote);
		if (!is_dquote && !is_squote)
		{
			if (check_pipe(data->readline_in, &i)
				|| check_hereappend(data->readline_in, &i)
				|| check_redirect(data->readline_in, &i))
			{
				status = 2;
				break ;
			}
		}
		i++;
	}
	status_ret(data, &status, is_squote, is_dquote);
	return (status);
}
