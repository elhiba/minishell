/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_utils0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:30:15 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/31 11:05:38 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	operation_len(char *str)
{
	if (str[0] == '>' && str[1] == '>')
		return (2);
	if (str[0] == '<' && str[1] == '<')
		return (2);
	if (str[0] == '<' || str[0] == '>')
		return (1);
	return (0);
}

int	arg_counter(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (operation_len(str + i))
		{
			count++;
			i += operation_len(str + i);
		}
		else
		{
			count++;
			while (str[i] && (str[i] != ' ' || str[i] == '\t')
				&& !operation_len(str + i))
				i++;
		}
	}
	return (count);
}

void	space_checker(char *str, t_token **tok, int index)
{
	if (!str[index]
		|| str[index] == ' '
		|| str[index] == '\t'
		|| operation_len(str + index))
		(*tok)->is_space_next = 1;
}

void	typer(t_token **token, char *arg)
{
	int	i;

	i = 0;
	if ((*token)->is_dquote || (*token)->is_squote)
		return ;
	if (arg[i] == '>' && arg[i + 1] == '>')
		(*token)->next->is_append = APPEND;
	else if (arg[i] == '<' && arg[i + 1] == '<')
		(*token)->next->is_heredoc = HEREDOC;
	else if (arg[i] == '>')
		(*token)->next->is_outfile = OUTPUT_FILE;
	else if (arg[i] == '<')
		(*token)->next->is_infile = INPUT_FILE;
}

/*
 * Ambiguous redirect
 * *here some cases where we have some issues!*
 * --------------------------------------------
 *  export a="ls -l"
 * --------------------------------------------
 *  echo hello > $a
 *  expected output:
 *  minishell: $a: ambiguous redirect
 * */
bool	is_space_(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}
