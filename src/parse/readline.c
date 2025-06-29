/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/29 21:13:29 by moel-hib         ###   ########.fr       */
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

void	multiple_pipes(t_data *data, t_cmd *cmd_list, char **env)
{
	t_cmd *current = cmd_list;
	t_cmd *last;
	int	fd[2];
	pid_t pid;
	int status = 0;
	while (current)
	{
		pipe(fd);
		if (current->cmd && !current->should_not_execute && !current->cmd_not_found)
		{
			pid = fork();
			if (pid == 0)
			{
				set_to_default();
				if (current->next && !current->cmd_not_found)
					dup2(fd[1], STDOUT_FILENO);
				if (current->STDIN != 0)
					dup2(current->STDIN, STDIN_FILENO);
				if (current->STDOUT != 1)
					dup2(current->STDOUT, STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				execve(current->cmd, current->argv, env);
				printf("minishell: %s: %s\n", current->argv[0], strerror(errno));
				if (errno == ENOENT)
					exit(127);
				else if (errno == ENOTDIR)
					exit (126);
				else
					exit (1);
			}
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		//printf("%d\n", current->cmd_not_found);
		//if (current->cmd_not_found)
		//	break;
		last = current;
		current = current->next;
	}
	if (last->cmd && !last->should_not_execute && !last->cmd_not_found)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->last_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			data->last_exit_code = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGSEGV)
				printf("%d Segmentation fault (core dumped) %s\n", pid, last->argv[0]);
			else if (WTERMSIG(status) == SIGTERM)
				printf("%d terminated %s", last->argv[0]);
		}
	}
	while ((pid = wait(&status)) > 0);
}



void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}


void	heredoc(t_cmd *cmd_list)
{
	t_cmd		*cmd;
	t_heredoc	*current;
	char		*buffer;
	pid_t		pid;

	cmd = cmd_list;
	current = NULL;
	while (cmd)
	{
		current = cmd->heredcs;
		while (current)
		{
			pid = fork();
			if (!pid)
			{
				set_to_default();
				while (1337)
				{
					buffer = readline("> ");
					if (!ft_strcmp(buffer, current->heredoc_del))
						break ;
					if (is_it_expandable(buffer) && current->expand)
						expand_variable_heredoc(cmd->data->env,&buffer);
					ft_putendl_fd(buffer, current->fd);
				}
				exit(0);
			}
			waitpid(pid, NULL, 0);
			close(current->fd);
			if (cmd->STDIN != 0)
				close(cmd->STDIN);
			cmd->STDIN = open(current->heredoc_file, O_RDONLY);
			current = current->next;
		}
		cmd = cmd->next;
	}
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
	list = NULL;
	if (!syntax_checker(data) && !all_spaces(data->readline_in))
	{
		//quotes_handler(data);
		args = ft_tokenizer(data);
		//if (args)
		//	print_list(args);
		//printf("\nEXEC LIST:\n\n");
		if (args)
			list = exec_setup(args, data);
		//if (list)
		//	pretty_print_cmd_list(list);
		/* This ft_builtin isn't helpfull here we will make changes later! */
		if (ft_builtin(list) == 0)
		{
			if (list)
				heredoc(list);
			if (list)
				check_errors(list, (t_token **)args);
			if (list)
				multiple_pipes(data, list, data->env);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdin);
		}
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

	if (!data || !data->argv)
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
	else
		status = 0;
	return (status);
}
