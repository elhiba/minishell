/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/15 10:44:31 by slasfar          ###   ########.fr       */
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

void	multiple_pipes(t_cmd *cmd_list, char **env)
{
	t_cmd *current = cmd_list;
	int	fd[2];
	pid_t pid;
	int status = 0;
	int	flag = 1;
	while (current)
	{
		pipe(fd);
		if (current->cmd)
			pid = fork();
		if (pid == 0) {
			if (current->next)
				dup2(fd[1], STDOUT_FILENO);
			if (current->STDIN != 0)
				dup2(current->STDIN, STDIN_FILENO);
			if (current->STDOUT != 1)
				dup2(current->STDOUT, STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			execve(current->cmd, current->argv, env);
			printf("minishell: %s: command not found!\n", current->cmd);
		}
		if (pid == 0)
			exit(-1);
		flag = 0;
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		current = current->next;
	}
	while ((pid = wait(&status)) > 0);
}

void	ft_parse(t_data *data)
{
	void	**args;
	t_cmd	*list;
	int saved_stdin = dup(STDIN_FILENO);
//	t_token	*token_list;
//	int		i;

//	i = 0;
//	token_list = NULL;
	if (!syntax_checker(data))
	{
		//quotes_handler(data);
		args = ft_tokenizer(data);
		if (!args)
			error_handler("split args", NULL);
		//print_list(args);
		//printf("\nEXEC LIST:\n\n");
		list = exec_setup(args, data);
		//if (list)
		//	pretty_print_cmd_list(list);
		if (list)
			multiple_pipes(list, data->env);
		dup2(saved_stdin, STDIN_FILENO);
	//	dollar_expand(data, token_list);
	//	data->token_list = token_list;
	//	if (ft_builtin(data) == 0 && token_list)
	//		ft_executioakn(data);
	//	else
	//		free_token_list(&token_list);
	}
}

int	ft_builtin(t_data *data)
{
	t_token	*tok_list;
	int		status;

	if (!data || !data->token_list || !data->token_list->arg)
		return (0);
	tok_list = data->token_list;
	if (ft_strcmp(tok_list->arg, "cd") == 0)
		status = do_cd(data);
	else if (ft_strcmp(tok_list->arg, "echo") == 0)
		status = do_echo(data);
	else if (ft_strcmp(tok_list->arg, "env") == 0)
		status = do_env(data);
	else if (ft_strcmp(tok_list->arg, "exit") == 0)
		status = do_exit(data);
	else if (ft_strcmp(tok_list->arg, "export") == 0)
		status = do_export(data);
	else if (ft_strcmp(tok_list->arg, "pwd") == 0)
		status = do_pwd(data);
	else if (ft_strcmp(tok_list->arg, "unset") == 0)
		status = do_unset(data);
	else
		status = 0;
	return (status);
}
