/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:55:28 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/19 15:46:39 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*read_rand(void)
{
	char	*buffer;
	int		fd;
	int		i;

	i = 0;
	buffer = ft_collector(17, ALLOC);
	ft_bzero(buffer, 17);
	fd = open("/dev/random", O_RDONLY);
	read(fd, buffer, 16);
	close(fd);
	while (i < 16)
	{
		buffer[i] = buffer[i] % 26 + 'a';
		if (!ft_isalpha(buffer[i]))
			buffer[i] = (i % 10) + 48;
		i++;
	}
	return (ft_strjoin("_", buffer));
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

void	add_to_argv(t_cmd *cmd, t_token *token)
{
	int	index;

	index = 0;
	while (cmd->argv[index])
		index++;
	cmd->argv[index++] = token->arg;
	cmd->argv[index] = NULL;
}

char	**realloc_argv(char **old_argv)
{
	char	**new_argv;
	int		i;

	i = 0;
	while (old_argv[i])
		i++;
	new_argv = ft_collector(sizeof(char *) * (i + 2), ALLOC);
	i = 0;
	while (old_argv[i])
	{
		new_argv[i] = old_argv[i];
		i++;
	}
	new_argv[i++] = ft_strdup("--color");
	new_argv[i] = NULL;
	return (new_argv);
}

char	*get_cmd_name(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
		i++;
	while (buffer[i] != '/' && i != 0)
		i--;
	if (buffer[i] == '/')
		i++;
	return (buffer + i);
}

int	is_a_builtin(char *name)
{
	if (!name)
		return (0);
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	else if (ft_strcmp(name, "echo") == 0)
		return (1);
	else if (ft_strcmp(name, "env") == 0)
		return (1);
	else if (ft_strcmp(name, "exit") == 0)
		return (1);
	else if (ft_strcmp(name, "export") == 0)
		return (1);
	else if (ft_strcmp(name, "pwd") == 0)
		return (1);
	else if (ft_strcmp(name, "unset") == 0)
		return (1);
	return (0);
}

char	*handle_empty_path(char *cmd_name)
{
	char	*tmp;

	tmp = ft_strjoin("./", cmd_name);
	if (access(tmp, X_OK) == 0 && !is_a_directory(tmp))
		return (tmp);
	else if (access(tmp, F_OK) == 0)
		return (tmp);
	return (NULL);
}

char	**cp_stock(char *cmd_name, char **path_stock)
{
	char	**tmp_stock;
	char	*new_name;
	int		i;

	i = 0;
	while (path_stock[i])
		i += 1;
	tmp_stock = ft_collector(sizeof(char *) * (i + 1), ALLOC);
	i = 0;
	while (path_stock[i])
	{
		new_name = ft_strjoin("/", cmd_name);
		tmp_stock[i] = ft_strjoin(path_stock[i], new_name);
		i++;
	}
	tmp_stock[i] = NULL;
	return (tmp_stock);
}

char	*check_for_cmd_existence(char **tmp_stock)
{
	int	i;

	i = 0;
	while (tmp_stock[i])
	{
		if (access(tmp_stock[i], X_OK) == 0 && !is_a_directory(tmp_stock[i]))
			return (tmp_stock[i]);
		i++;
	}
	i = 0;
	while (tmp_stock[i])
	{
		if (access(tmp_stock[i], F_OK) == 0)
			return (tmp_stock[i]);
		i++;
	}
	return (NULL);
}

char	*get_full_path(char **path_stock, char *cmd_name, int *not_found)
{
	int		i;
	char	**tmp_stock;
	char	*cmd_path;
	char	*tmp;

	i = 0;
	cmd_path = NULL;
	while (path_stock[i])
		i += 1;
	if (i == 0)
	{
		tmp = handle_empty_path(cmd_name);
		if (tmp)
			return (tmp);
	}
	tmp_stock = cp_stock(cmd_name, path_stock);
	i = 0;
	cmd_path = check_for_cmd_existence(tmp_stock);
	if (cmd_path)
		return (cmd_path);
	if (!is_a_builtin(cmd_name))
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

int	set_cmd_name(t_cmd *cmd, t_token *token, t_data *data)
{
	t_env	*envp;
	char	**stock;

	envp = ft_collector(sizeof(t_env), ALLOC);
	envp->name = ft_strdup("PATH");
	envp->name_len = 4;
	get_env_value(data->env, envp);
	stock = ft_split(envp->value, ':');
	if (*token->arg && check_absolute_path(token->arg))
		cmd->cmd = get_full_path(stock, token->arg, &cmd->cmd_not_found);
	else
		cmd->cmd = token->arg;
	if (!*token->arg && (token->is_dquote || token->is_squote))
		cmd->cmd_not_found = 1;
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
	char		*heredoc_name;
	t_heredoc	*heredoc_node;

	(void)data;
	heredoc_node = ft_collector(sizeof(t_heredoc), ALLOC);
	heredoc_node->heredoc_del = token->arg;
	heredoc_name = ft_strjoin("heredoc", read_rand());
	heredoc_name = ft_strjoin("/tmp/", heredoc_name);
	heredoc_node->heredoc_file = heredoc_name;
	heredoc_node->expand = 1;
	if (token->is_dquote || token->is_squote)
		heredoc_node->expand = 0;
	add_heredoc(&cmd->heredcs, heredoc_node);
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
	node->stdin_ = 0;
	node->stdout_ = 1;
	node->next = NULL;
}

int	empty_env_var(t_token *current)
{
	if (current->is_env_var && !is_redir(current)
		&& !current->prev && !current->next
		&& !current->is_dquote && !current->arg[0])
		return (1);
	return (0);
}

int	is_valid_cmd_name(t_token *current)
{
	if ((current->is_dquote
			|| current->is_word
			|| current->is_squote
			|| current->is_env_var)
		&& !(current->is_env_var
			&& !current->is_dquote
			&& !current->arg[0])
		&& !is_redir(current)
		&& !current->is_ambiguous)
		return (1);
	return (0);
}

void	do_while(t_token *current, t_cmd *node, t_data *data, int *flag)
{
	if (current->is_heredoc == HEREDOC)
		handle_heredoc(node, current, data);
	else if (flag && is_valid_cmd_name(current))
	{
		*flag = 0;
		if (set_cmd_name(node, current, data) == -1)
			node->should_not_execute = 1;
	}
	else if (!(current->is_env_var && !current->arg[0] && !current->is_dquote)
		&& !current->is_ambiguous
		&& !is_redir(current))
		add_to_argv(node, current);
}

void	cmd_builder(t_cmd **cmd_list, t_token *head, t_data *data)
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
		do_while(current, node, data, &flag);
		current = current->next;
	}
	if (node->cmd && !ft_strcmp("ls", get_cmd_name(node->argv[0])))
		node->argv = realloc_argv(node->argv);
	add_cmd(cmd_list, node);
}

t_cmd	*exec_setup(void	**stock, t_data *data)
{
	t_cmd	*cmd_list;
	int		i;

	i = 0;
	cmd_list = NULL;
	while (stock[i])
	{
		cmd_builder(&cmd_list, (t_token *)stock[i], data);
		i++;
	}
	return (cmd_list);
}
