/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 12:10:29 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/19 12:10:49 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

int	check_pipe(char *str, int *i)
{
	if (str[*i] == '|')
	{
		while (str[*i + 1] == ' ')
			(*i)++;
		if (str[*i + 1] == '|' || str[*i + 1] == '\0')
		{
			if (str[*i + 1] == '\0')
			{
				printf("%s `newline'\n", SYN_OP_ERROR);
				return (2);
			}
			printf("%s `%c'\n", SYN_OP_ERROR, *check_op(str + (*i + 1)));
			return (2);
		}
	}
	return (0);
}

int	check_redirect(char *str, int *i)
{
	if ((str[*i] == '>' && str[*i + 1] != '>')
		|| (str[*i] == '<' && str[*i + 1] != '<'))
	{
		while (str[*i + 1] == ' ')
			(*i)++;
		if (check_op(str + (*i + 1)) || str[*i + 1] == '\0')
		{
			if (str[*i + 1] == '\0')
			{
				printf("%s `newline'\n", SYN_OP_ERROR);
				return (2);
			}
			printf("%s `%c'\n", SYN_OP_ERROR, *check_op(str + (*i + 1)));
			return (2);
		}
	}
	return (0);
}

int	check_hereappend(char *str, int *i)
{
	if ((str[*i] == '<' && str[*i + 1] == '<')
		|| (str[*i] == '>' && str[*i + 1] == '>'))
	{
		while (str[*i + 2] == ' ')
			(*i)++;
		if (check_op(str + (*i + 2)) || str[*i + 2] == '\0')
		{
			if (str[*i + 2] == '\0')
			{
				printf("%s `newline'\n", SYN_OP_ERROR);
				return (2);
			}
			printf("%s `%s'\n", SYN_OP_ERROR, check_op(str + (*i + 2)));
			return (2);
		}
	}
	return (0);
}
