/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:10:02 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/08 14:18:48 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_op(char *str)
{
	if (str[0] == '>' && str[1] == '>')
		return (">>");
	if (str[0] == '<' && str[1] == '<')
		return ("<<");
	if (str[0] == '<')
		return ("<");
	if (str[0] == '>')
		return (">");
	if (str[0] == '|')
		return ("|");
	return (0);
}

int		check_pipe(char *str, int *i)
{
	if (str[*i] == '|')
	{
		while (str[*i + 1] == ' ')
			(*i)++;
		if (str[*i + 1] == '|' || str[*i + 1] == '\0')
		{
			printf(SYN_ERROR);
			if (str[*i + 1] == '\0')
			{
				printf("`newline'\n");
				return (2);
			}
			printf("`%c'\n", *check_op(str + (*i + 1)));
			return (2);
		}
	}
	return 0;
}

int		check_redirect(char *str, int *i)
{
	if ((str[*i] == '>' && str[*i + 1] != '>')
		|| (str[*i] == '<' && str[*i + 1] != '<'))
	{
		while (str[*i + 1] == ' ')
			(*i)++;
		if (check_op(str + (*i + 1)) || str[*i + 1] == '\0')
		{
			printf(SYN_ERROR);
			if (str[*i + 1] == '\0')
			{
				printf("`newline'\n");
				return (2);
			}
			printf("`%c'\n", *check_op(str + (*i + 1)));
			return (2);
		}
	}
	return (0);
}

int		check_hereappend(char *str, int *i)
{
	if ((str[*i] == '<' && str[*i + 1] == '<')
		|| (str[*i] == '>' && str[*i + 1] == '>'))
	{
		while (str[*i + 2] == ' ')
			(*i)++;
		if (check_op(str + (*i + 2)) || str[*i + 2] == '\0')
		{
			printf(SYN_ERROR);
			if (str[*i + 2] == '\0')
			{
				printf("`newline'\n");
				return (2);
			}
			printf("`%s'\n", check_op(str + (*i + 2)));
			return (2);
		}
	}
	return (0);
}

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

int		syntax_checker(t_data *data)
{
	int		i;
	int		status;
	int		is_dquote;
	int		is_squote;
	
	i = 0;
	status = 0;
	is_dquote = 0;
	is_squote = 0;
	while (data->readline_in[i])
	{
		check_quotes(data->readline_in, i, &is_dquote, &is_squote);
		if (!is_dquote && !is_squote)
		{
			if ((status = check_pipe(data->readline_in, &i)))
				break ;
			if ((status = check_hereappend(data->readline_in, &i)))
				break ;
			else if ((status = check_redirect(data->readline_in, &i)))
				break ;
		}
		i++;
	}
	data->last_exit_code = status;
	return (status);
}
