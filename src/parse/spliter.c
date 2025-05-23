/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:42:44 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/20 11:32:07 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		operation_len(char *str)
{
	if (str[0] == '>' && str[1] == '>')
		return (2);
	if (str[0] == '<' && str[1] == '<')
		return (2);
	if (str[0] == '<' || str[0] == '>')
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

char	**ft_spliter(char *str)
{
	char	**args;
	int		op_len;
	int		index;
	int		i;
	int		start;

	i = 0;
	index = 0;
	args = (char **)malloc(sizeof(char *) * (arg_counter(str) + 1));
	if (!args)
		error_handler("malloc: I can't anymore!", NULL);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		op_len = operation_len(str + i);
		if (op_len)
		{
			args[index] = ft_substr(str, i, op_len);
			index++;
			i += op_len;
		}
		else
		{
			start = i;
			while (str[i] && !(str[i] == ' ') && !operation_len(str + i))
				i++;
			args[index] = ft_substr(str, start, i - start);
			index++;
		}
	}
	args[index] = NULL;
	return (args);
}

t_token	*token(char *str)
{
	t_token *tok;
	char	**args;
	int		i;

	i = 0;
	tok = NULL;
	args = ft_spliter(str);
	if (!args)
		error_handler("I can't split!", NULL);
	while (args[i])
	{
		add_token_node(&tok, args[i]);
		i++;
	}
	return (tok);
}

void	**ft_tokenizer(t_data *data)
{
	void	**tok;
	char	**ptok;
	int		i;

	i = 0;
	ptok = special_split(data->readline_in, '|');
	if(!ptok)
		error_handler("I can't split pipes!", data);
	while (ptok[i])
		i++;
	tok = (void **)malloc(sizeof(void *) * (i + 1));
	if (!tok)
		error_handler("malloc: I can't fr!", data);
	i = 0;
	while (ptok[i])
	{
		tok[i] = token(ptok[i]);
		i++;
	}
	tok[i] = NULL;
	return (tok);
}
