/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:55:28 by slasfar           #+#    #+#             */
/*   Updated: 2025/06/21 00:51:08 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char *ft_random(char **env)
{
	int	fd[2];
	int	pid;
	char	**argv;
	char *buffer;

	argv = ft_collector(sizeof(char *) * 5, ALLOC);
	memcpy(argv, (char *[]){"openssl", "rand", "-hex", "8", NULL}, sizeof(char *) * 5);
	buffer = ft_collector(17, ALLOC);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execve("/bin/openssl", argv, env);
	}
	close(fd[1]);
	read(fd[0], buffer, 16);
	return (ft_strjoin("_", buffer));
}

bool	is_redir(t_token *current)
{
	if (current->is_infile || current->is_outfile
		|| current->is_heredoc || current->is_append)
		return (true);
	return (false);
}

int	count_heredoc(t_token *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (head->is_heredoc)
			count++;
		head = head->next;
	}
	return (count);
}

int	count_argv(t_token *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (!is_redir(head))
			count++;
		head = head->next;
	}
	return (count);
}


char *get_full_path(char **path_stock, char *cmd_name, int *not_found)
{
	int		i;
	int		len;
	char	**tmp_stock;
	char	*new_name;

	(1) && (i = 0, len = 0);
	while (path_stock[i])
		(1) && (len += 1, i += 1);
	tmp_stock = ft_collector(sizeof(char *) * (len + 1), ALLOC);
	i = 0;
	while (path_stock[i])
	{
		new_name = ft_strjoin("/", cmd_name);
		tmp_stock[i] = ft_strjoin(path_stock[i], new_name);
		i++;
	}
	tmp_stock[i] = NULL;
	i = 0;
	while (tmp_stock[i])
	{
		if (access(tmp_stock[i], X_OK) == 0)
			return (tmp_stock[i]);
		i++;
	}
	*not_found = 1;
	return (cmd_name);
}

int	check_absolute_path(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

char	*check_if_correct(char *path)
{
	if (access(path, X_OK) == 0)
		return (path);
	return (path);
}

int	is_a_directory(char *cmd)
{
	struct stat statbuf;

	ft_bzero(&statbuf, sizeof(statbuf));
	stat(cmd, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
		return (1);
	return (0);
}

int	check_for_err(t_cmd *cmd)
{
	//if (access(cmd->cmd, F_OK) != 0)
	//	return (printf("minishell: %s: No such file or directory\n", cmd->cmd), -1);
	if (is_a_directory(cmd->cmd))
		return (printf("minishell: %s: Is a directory\n", cmd->cmd), -1);
	else if (access(cmd->cmd, F_OK) == 0)
	{
		if (access(cmd->cmd, X_OK) != 0)
			return (printf("minishell: %s: Permission denied\n", cmd->cmd), -1);
	}
	return (0);
}

int	set_cmd_name(t_cmd *cmd, t_token *token, t_data *data)
{
	t_env	*envp;
	char	**stock;

	envp = ft_collector(sizeof(t_env), ALLOC);
	envp->name = ft_strdup("PATH");
	envp->name_len = 4;
	get_env_value(data->env, envp);
	stock = ft_split(envp->value, ':');
	if (!*token->arg && token->is_env_var && token->is_word)
		return (-1);
	else if (!*token->arg && (token->is_dquote || token->is_squote))
		return(printf("minishell: '%s': command not found!\n", token->arg), -1);
	if (*token->arg && check_absolute_path(token->arg))
	{
		cmd->cmd = get_full_path(stock, token->arg, &cmd->cmd_not_found);
	
		if (cmd->cmd_not_found)
			printf("minishell: %s: command not found!\n", cmd->cmd);
	}
	else if (*token->arg)
	{
		cmd->cmd = token->arg;
		if (check_for_err(cmd) == -1)
			return (-1);
	}
	cmd->argv[0] = ft_strdup(token->arg);
	cmd->argv[1] = NULL;
	return (0);
}

void	add_heredoc(t_heredoc **head, t_heredoc *new)
{
	t_heredoc	*curr;

	curr = *head;
	if (!*head)
		*head = new;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	handle_heredoc(t_cmd *cmd, t_token *token, t_data *data)
{
	int	i;
	int	len;
	char	*heredoc_name;
	t_heredoc	*heredoc_node;

	heredoc_node = ft_collector(sizeof(t_heredoc), ALLOC);
	len = 0;
	i = 0;
	heredoc_node->heredoc_del = token->arg;
	heredoc_name = ft_strjoin("heredoc", ft_random(data->env));
	heredoc_name = ft_strjoin("/tmp/", heredoc_name);
	heredoc_node->heredoc_file = heredoc_name;
	cmd->STDIN = open(heredoc_name, O_CREAT | O_WRONLY | O_RDONLY, 0644);
		//return (perror("minishell"), -1);
	heredoc_node->fd = cmd->STDIN;
	add_heredoc(&cmd->heredcs, heredoc_node);
}

int	set_fd(t_cmd *cmd, t_token *token, t_data *data)
{
	if (token->is_heredoc == HEREDOC)
		handle_heredoc(cmd, token, data);
	if (token->is_outfile == OUTPUT_FILE)
	{
		if (cmd->STDOUT != 1)
			close(cmd->STDOUT);
		cmd->STDOUT = open(token->arg, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd->STDOUT == -1)
			return (perror("minishell"), -1);
	}
	else if (token->is_append == APPEND)
	{
		if (cmd->STDOUT != 1)
			close(cmd->STDOUT);
		cmd->STDOUT = open(token->arg, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (cmd->STDOUT == -1)
			return (perror("minishell"), -1);
	}
	else if (token->is_infile == INPUT_FILE)
	{
		if (cmd->STDIN != 0)
			close(cmd->STDIN);
		cmd->STDIN = open(token->arg, O_RDONLY, 0644);
		if (cmd->STDIN == -1)
			return (perror("minishell"), -1);
	}
	return (0);
}


void	add_to_argv(t_cmd *cmd, t_token *token)
{
	int	index;

	index = 0;
	while(cmd->argv[index])
		index++;
	cmd->argv[index++] = token->arg;
	cmd->argv[index] = NULL;
}

void	add_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*curr;

	curr = *cmd;
	if (!*cmd)
		*cmd = new;
	else
	{
		curr = *cmd;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	init_stuff(t_token *head, t_cmd *node)
{
	node->cmd = NULL;
	node->argv = ft_collector(sizeof(char *) * (count_argv(head) + 1), ALLOC);
	node->argv[0] = NULL;
	node->heredcs = NULL;
	node->STDIN = 0;
	node->STDOUT = 1;
	node->next = NULL;
}

int	check_redir_err(t_token *current)
{
	if (is_a_directory(current->arg))
		return (printf("minishell: %s: is a directory\n", current->arg), -1);
	if (current->is_infile && access(current->arg, F_OK) != 0)
		return (printf("minishell: %s: No such file or directory\n", current->arg), -1);
	return (0);
}

int	cmd_builder(t_cmd **cmd_list, t_token *head, t_data *data)
{
	t_token	*current;
	t_cmd	*node;
	int		flag;

	flag = 1;
	node = ft_collector(sizeof(t_cmd), ALLOC);
	init_stuff(head, node);
	node->data = data;
	current = head;
	while (current)
	{
		if (is_redir(current))
		{
			if (check_redir_err(current) == -1)
				node->should_not_execute = 1;
			else if (set_fd(node, current, data) == -1)
				node->should_not_execute = 1;
		}
		else if(flag && (current->is_dquote
				|| current->is_word
				|| current->is_squote
				|| current->is_env_var))
		{
			flag = 0;
			if (set_cmd_name(node, current, data) == -1)
				node->should_not_execute = 1;
		}
		else if (!(current->is_env_var && !current->arg[0] && !current->is_dquote))
			add_to_argv(node, current);
		current = current->next;
	}
	add_cmd(cmd_list, node);
	return (0);
}

t_cmd	*exec_setup(void	**stock, t_data *data)
{
	t_cmd	*cmd_list;
	int	i;

	i = 0;
	cmd_list = NULL;
	while (stock[i])
	{
		if (cmd_builder(&cmd_list, (t_token *)stock[i], data) == -1)
			return (NULL);
		i++;
	}
	return (cmd_list);
}


void	pretty_print_cmd_list(t_cmd *cmd_list)
{
	int i;
	int cmd_num = 1;

	if (!cmd_list)
	{
		printf("----------------------------------------\n");
		printf("|           Command List is Empty      |\n");
		printf("----------------------------------------\n");
		return;
	}

	while (cmd_list)
	{
		printf("\n.---------------------------------------.\n");
		printf("|               COMMAND %-3d             |\n", cmd_num++);
		printf(":---------------------------------------:\n");

		printf("| %-12s: %s\n", "Command", cmd_list->cmd ? cmd_list->cmd : "(null)");
		printf(":---------------------------------------:\n");


		if (cmd_list->argv && cmd_list->argv[0])
		{
			printf("| %-12s: [%s]\n", "argv[0]", cmd_list->argv[0]);
			i = 1;
			while (cmd_list->argv[i])
			{
				printf("| %-12s  [%s]\n", "", cmd_list->argv[i]);
				i++;
			}
		}
		else
		{
			printf("| %-12s: (empty)\n", "argv");
		}
		printf(":---------------------------------------:\n");

		printf("| %-12s: %d\n", "STDIN", cmd_list->STDIN);
		printf("| %-12s: %d\n", "STDOUT", cmd_list->STDOUT);
		printf("| %-12s: %d\n", "NOT FOUND", cmd_list->cmd_not_found);
		printf(":---------------------------------------:\n");

		t_heredoc *current_heredoc = cmd_list->heredcs;
		if (current_heredoc)
		{
			int heredoc_num = 1;
			while (current_heredoc)
			{
				printf("| Heredoc #%-2d\n", heredoc_num++);
				printf("|   %-10s: [%s]\n", "Delimiter", current_heredoc->heredoc_del ? current_heredoc->heredoc_del : "(null)");
				printf("|   %-10s: [%s]\n", "File", current_heredoc->heredoc_file ? current_heredoc->heredoc_file : "(null)");
				printf("|   %-10s: %d\n", "FD", current_heredoc->fd);

				current_heredoc = current_heredoc->next;
				if (current_heredoc)
				{
				    printf(":.......................................:\n");
				}
			}
		}
		else
		{
			printf("| %-12s: (none)\n", "Heredocs");
		}

		printf("'---------------------------------------'\n");

		cmd_list = cmd_list->next;
	}
}
