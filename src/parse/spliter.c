/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:42:44 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/26 21:37:33 by slasfar          ###   ########.fr       */
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
	if (!str[index] || str[index] == ' ' || operation_len(str + index))
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
		(*token)->next->is_append = APPEND;
	else if (arg[i] == '<' && arg[i + 1] == '<')
		(*token)->next->is_heredoc = HEREDOC;
	else if (arg[i] == '>')
		(*token)->next->is_outfile = OUTPUT_FILE;
	else if (arg[i] == '<')
		(*token)->next->is_infile = INPUT_FILE;
//	i++;
//	}
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

 static int	ft_counter(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		while (is_space_(str[i]))
			i++;
		if (str[i])
			counter++;
		while (str[i] && !is_space_(str[i]))
			i++;
	}
	return (counter);
}

void	add_tmp(t_token **head,t_token *new)
{
	t_token	*curr;

	if (!*head)
		*head = new;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
		new->prev = curr;
	}
}

void	cp_flag(t_token *dest, t_token *src)
{
	dest->is_dquote = src->is_dquote;
	dest->is_env_var = src->is_env_var;
	dest->is_squote = src->is_squote;
	dest->is_word = src->is_word;
	dest->is_space_next = src->is_space_next;
	dest->is_not_splittable = src->is_not_splittable;
	dest->is_heredoc = src->is_heredoc;
	dest->is_append = src->is_append;
	dest->is_outfile = src->is_outfile;
	dest->is_infile = src->is_infile;
}

int	joining_result(t_token	*token, t_data *data)
{
	t_token	*tmp_list;
	t_token	*current;
	int		i;

	i = 0;
	tmp_list = NULL;
	while (token)
	{
		current = ft_collector(sizeof(t_token), ALLOC);
		current->arg = ft_strdup(token->arg);
		cp_flag(current, token);
		add_tmp(&tmp_list, current);
		if (token->is_space_next)
			break ;
		token = token->next;
	}
	split_expanded(&tmp_list, data);
	join_tokens(&tmp_list);
	current = tmp_list;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

int	additional_check(t_token *token)
{
	t_token	*current;

	current = token;
	while (current && !current->is_env_var)
		current = current->next;
	if (current->arg[0] && all_spaces(current->arg) && (!current->prev->is_space_next && !current->is_space_next))
		return (1);
	return (0);	
}

void	build_error_name(t_token *token)
{
	char	*error_name;
	t_token	*current;

	current = token;
	error_name = ft_strdup("");
	while (current)
	{
		if (current->is_env_var && current->is_word)
			error_name = ft_strjoin(error_name, current->key);
		else if (current->is_env_var && current->is_dquote)
			error_name = ft_strjoin(error_name, ft_strjoin("\"", ft_strjoin(current->key, "\"")));
		else if (current->is_word)
			error_name = ft_strjoin(error_name, current->arg);
		else if (current->is_dquote)
			error_name = ft_strjoin(error_name, ft_strjoin("\"", ft_strjoin(current->arg, "\"")));
		else if (current->is_squote)
			error_name = ft_strjoin(error_name, ft_strjoin("\'", ft_strjoin(current->arg, "\'")));
		if (current->is_space_next)
			break ;
		current = current->next;
	}
	token->ambiguous_name = error_name;
}

void	set_ambiguous(t_token *token, t_data *data)
{
	t_token *current;
	t_token	*next;
	t_token	*tmp;

	current = token;
	next = current->next;
	while (current)
	{
		if (is_redirect(current, current->arg) && !current->next->is_not_splittable)
		{
			next = current->next;
			if (!next->is_dquote && (!ft_strcmp(next->arg, "") || all_spaces(next->arg)) && (!next->next || (next->is_space_next)))
				next->is_ambiguous = 1;
			if (joining_result(next, data) > 1)
				next->is_ambiguous = 1;
			if (additional_check(next))
				next->is_ambiguous = 1;
			if (next && next->is_ambiguous)
			{
				build_error_name(next);
				tmp = next;
				while (tmp)
				{
					tmp->is_ambiguous = 1;
					if (tmp->is_space_next)
						break;
					tmp = tmp->next;
				}
				//printf("%s is sus\n", next->ambiguous_name);
			}
		}
		current = current->next;
	}
}

void	ft_spliter(t_token **token, char *str, t_data *data)
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
			add_token_node(token, ft_substr(str, i, op_len));
			//if (!arg)
			//	error_handler("ft_substr", NULL);
			i += op_len;
		}
		else
		{
			start = i;
			//if (str[i] == '$')
			//	arg = dollar_handler(str, &i);
			if (str[i] == '\'' || str[i] == '\"')
				add_token_node(token, quotes_handler(str, &i, &op_len)) ;
			else
			{
				while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '\"' && !operation_len(str + i))
					i++;
				add_token_node(token, ft_substr(str, start, i - start));
				op_len = 1337;
			}
			//if (!arg)
			//	error_handler("ft_substr", NULL);
			//args[index] = ft_substr(str, start, i - start);
			//index++;
		}
		//if (check_is_expandable(arg) && op_len != 11) {
		//	start = 1337;
		//	expand_variable(data->env, &arg);
		//}
		//printf("%s\n", arg);
		//add_token_node(token, arg);
		ptr = *token;
		while (ptr->next){
			ptr = ptr->next;
		}
		//printf("%s %s %d\n", ptr->arg,__func__, __LINE__);
		//typer(&ptr, arg);
		if (op_len == 10)
			ptr->is_dquote = 1;
		else if (op_len == 11)
			ptr->is_squote = 1;
		else if (op_len == 1337)
			ptr->is_word = 1;
		//if (start == 1337)
		//	ptr->is_env_var = 1;
		//else
		//	ptr->is_env_var = 0;
		space_checker(str, &ptr, i);
	}	
	//ambiguous_redirect(token);
	check_and_expand(token, data, data->env);
	set_ambiguous(*token, data);
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
	//t_token	*current;

	ptr = *head;
	while (ptr)
	{
	//	current = ptr;
		if ((!ptr->is_squote &&!ptr->is_dquote && !ptr->is_env_var) && operator_cleaner(ptr->arg))
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
		}
		ptr = ptr->next;
	}
}


void	remove_empty_env(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current)
	{
		if (!current->prev && current->is_env_var &&ft_strcmp(current->arg, "") == 0 && !current->is_dquote)
		{
			*head = current->next;
			if (current->next)
				current->next->prev = *head;
		}
		else if (current->is_env_var &&ft_strcmp(current->arg, "") == 0 && !current->is_dquote)
		{
			current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
		}
		current = current->next;
	}
}

int	is_redirect(t_token *current, char *arg)
{
	int	i;

	i = 0;
	if (current->is_dquote || current->is_squote)
		return (0);
	if (arg[i] == '>' && arg[i + 1] == '>')
		return (1);
	else if (arg[i] == '>')
		return (1);
	else if (arg[i] == '<')
		return (1);
	return (0);
}


t_token	*token(char *str, t_data *data)
{
	t_token	*tok;
	t_token	*ptr;
	//char	**args;
	//int		i;

	//i = 0;
	tok = NULL;
	ft_spliter(&tok, str, data);
	//remove_empty_env(&tok);
	split_expanded(&tok, data);
	join_tokens(&tok); // join tokens with is_space_next == 0;
	//check_ambiguous(tok);
	//if (fail)
	//	reuturn NULL;
	
	ptr = tok;
	while (ptr)
	{
		typer(&ptr, ptr->arg);
		ptr = ptr->next;
	}
	//if(check_ambiguous(tok) == -1)
	//	return (NULL);
	node_cleaner(&tok);
	//split_expanded(&tok, data);
	//join_tokens(&tok);
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
	tok = ft_collector(sizeof(void *) * (i + 1), ALLOC);
	if (!tok)
		ft_collector(0, EXIT);
	i = 0;
	while (ptok[i])
	{
		tok[i] = token(ptok[i], data);
		if (!tok[i])
			return (NULL);
		i++;
	}
	tok[i] = NULL;
	return (tok);
}
