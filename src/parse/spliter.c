/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:42:44 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/27 17:35:56 by slasfar          ###   ########.fr       */
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

void	space_checker(char *str, t_token **tok, int index)
{
	if (str[index] == ' ' || operation_len(str + index))
		(*tok)->is_space_next = 1;
}

void	typer(t_token **token, char *arg)
{
	int	i;

	i = 0;
//	while (arg[i])
//	{
	if ((*token)->is_dquote || (*token)->is_squote)
		return ;
	if (arg[i] == '>' && arg[i + 1] == '>')
		(*token)->next->is_redirection = REDIRECTION;
	else if (arg[i] == '<' && arg[i + 1] == '<')
		(*token)->next->is_heredoc = HEREDOC;
	else if (arg[i] == '>')
		(*token)->next->is_outfile = OUTPUT_FILE;
	else if (arg[i] == '<')
		(*token)->next->is_infile = INPUT_FILE;
//	i++;
//	}
}

void	ft_spliter(t_token **token, char *str)
{
	//char	**args;
	//int		index;
	t_token	*ptr;
	char	*arg;
	int		op_len;
	int		i;
	int		start;

	i = 0;
	//index = 0;
//	args = (char **)malloc(sizeof(char *) * (arg_counter(str) + 1));
//	if (!args)
//		error_handler("malloc", NULL);
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		op_len = operation_len(str + i);
		if (op_len)
		{
			//args[index] = ft_substr(str, i, op_len);
			//index++;
			arg = ft_substr(str, i, op_len);
			if (!arg)
				error_handler("ft_substr", NULL);
			i += op_len;
		}
		else
		{
			start = i;
			while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"' && !operation_len(str + i))
				i++;
			if (str[i] == '\'' || str[i] == '\"')
				arg = quotes_handler(str, &i, &op_len);
			else
				arg = ft_substr(str, start, i - start);
			if (!arg)
				error_handler("ft_substr", NULL);
			//args[index] = ft_substr(str, start, i - start);
			//index++;
		}
		add_token_node(token, arg);
		ptr = *token;
		while (ptr->next)
			ptr = ptr->next;
		//typer(&ptr, arg);
		if (op_len == DOUBLE_QUOTE)
			ptr->is_dquote = 1;
		else if (op_len == SINGLE_QUOTE)
			ptr->is_squote = 1;
		space_checker(str, &ptr, i);
	}
	// hnaaaaa :)
	/*
	expand;
	split white spaces;
	*/
	//quotes_handler(token);
	//args[index] = NULL;
	//return (args);
}

int		operator_cleaner(char *arg)
{
	if (arg[0] == '>' && arg[1] == '>' && arg[2] == '\0')
		return (2);
	if (arg[0] == '<' && arg[1] == '<' && arg[2] == '\0')
		return (2);
	if ((arg[0] == '<' || arg[0] == '>') && arg[1] == '\0')
		return (1);
	return (0);
}

void	node_cleaner(t_token **head)
{
	t_token	*ptr;
	t_token	*current;

	ptr = *head;
	while (ptr)
	{
		current = ptr;
		if (operator_cleaner(ptr->arg))
		{
			if (!ptr->prev)
			{
				*head = ptr->next;
				(*head)->prev = NULL;
			}
			ptr = ptr->next;
			if (ptr->prev)
			{
				ptr->prev = ptr->prev;
				ptr->prev->prev->next = ptr;
			}
			free(current->arg);
			free(current);
		}
		ptr = ptr->next;
	}
}

t_token	*token(char *str)
{
	t_token	*tok;
	t_token	*ptr;
	//char	**args;
	//int		i;

	//i = 0;
	tok = NULL;
	ft_spliter(&tok, str);
	ptr = tok;
	while (ptr)
	{
		typer(&ptr, ptr->arg);
		ptr = ptr->next;
	}
	node_cleaner(&tok);
	//if (!args)
	//	error_handler("args", NULL);
//	while (args[i])
//	{
//		add_token_node(&tok, args[i]);
//		i++;
//	}
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
		error_handler("pipe split", data);
	while (ptok[i])
		i++;
	tok = (void **)malloc(sizeof(void *) * (i + 1));
	if (!tok)
		error_handler("malloc", data);
	i = 0;
	while (ptok[i])
	{
		tok[i] = token(ptok[i]);
		i++;
	}
	tok[i] = NULL;
	return (tok);
}
