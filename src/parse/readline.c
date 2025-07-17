/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/17 17:25:49 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list(void **head)
{
	t_token	**ptr;
	t_token	*current;
	int		i;
	int		is_newline;

	i = 0;
	ptr = (t_token **)head;
	while (ptr[i])
	{
		current = ptr[i];
		printf("Args[%i]: ", i);
		while (current)
		{
			printf("{%s}", current->arg);
			current = current->next;
		}
		printf("\n");
		i++;
	}

	i = 0;
	while (ptr[i])
	{
		is_newline = 0;
		current = ptr[i];
		while (current)
		{
			if (current->is_infile || current->is_outfile || current->is_heredoc || current->is_append)
			{
				printf("Args[-%i-]: ", i);
				break ;
			}
			current = current->next;
		}
		current = ptr[i];
		while (current)
		{
			if (current->is_infile)
				printf("{\E[31m%s\E[0m} is input file\t", current->arg), is_newline = 1;
			if (current->is_outfile)
				printf("{\E[31m%s\E[0m} is out file\t", current->arg), is_newline = 1;
			if (current->is_heredoc)
				printf("{\E[31m%s\E[0m} is here doc\t", current->arg), is_newline = 1;
			if (current->is_append)
				printf("{\E[31m%s\E[0m} is redirection (appending)\t", current->arg), is_newline = 1;
			current = current->next;
		}
		if (is_newline)
			printf("\n");
		i++;
	}
}


void	ft_parse(t_data *data)
{
	void	**args;
	t_cmd	*list;
//	t_token	*token_list;
//	int		i;

//	i = 0;
//	token_list = NULL;
	list = NULL;
	if (!syntax_checker(data) && !all_spaces(data->readline_in))
	{
		//quotes_handler(data);
		args = ft_tokenizer(data);
		// if (args)
			// print_list(args);
		//printf("\nEXEC LIST:\n\n");
		if (args)
			list = exec_setup(args, data);
		// if (list)
		// 	pretty_print_cmd_list(list);
		/* This ft_builtin isn't helpfull here we will make changes later! */
		if (list)
			heredoc(list);
		if (list)
			check_errors(list, (t_token **)args);
		if (list)
			execute(list, data);
	//	dollar_expand(data, token_list);
	//	data->token_list = token_list;
	//	if (ft_builtin(data) == 0 && token_list)
	//		ft_executioakn(data);
	//	else
	//		free_token_list(&token_list);
	}
}

int	ft_builtin(t_cmd *data)
{
	t_cmd	*ptr;
	int		status;

	if (data->should_not_execute)
		return (1337);
	if ((!data || !data->argv))
		return (0);
	ptr = data;
	if (ft_strcmp(*ptr->argv, "cd") == 0)
		status = do_cd(data);
	else if (ft_strcmp(*ptr->argv, "echo") == 0)
		status = do_echo(data);
	else if (ft_strcmp(*ptr->argv, "env") == 0)
		status = do_env(data);
	else if (ft_strcmp(*ptr->argv, "exit") == 0)
		status = do_exit(data);
	else if (ft_strcmp(ptr->cmd, "export") == 0)
		status = do_export(data);
	else if (ft_strcmp(*ptr->argv, "pwd") == 0)
		status = do_pwd(data);
	else if (ft_strcmp(*ptr->argv, "unset") == 0)
		status = do_unset(data);
	return (0);
}
