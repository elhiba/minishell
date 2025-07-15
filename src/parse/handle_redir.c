/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:55:28 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/15 16:25:07 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *read_rand()
{
	char 	*buffer;
	int		fd;
    int     i = 0;

	buffer = malloc(17);
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
	while(cmd->argv[index])
		index++;
	cmd->argv[index++] = token->arg;
	cmd->argv[index] = NULL;
}

char **realloc_argv(char **old_argv)
{
	char 	**new_argv;
	int		i;

	i = 0;
	while(old_argv[i])
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

char *get_cmd_name(char *buffer)
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


char *get_full_path(char **path_stock, char *cmd_name, int *not_found)
{
	int		i;
	char	**tmp_stock;
	char	*new_name;

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
	i = 0;
	while (tmp_stock[i]) // check first with X_OK
	{
		if (access(tmp_stock[i], X_OK) == 0 && !is_a_directory(tmp_stock[i]))
			return (tmp_stock[i]);
		i++;
	}
	i = 0;
	while (tmp_stock[i]) // check second with F_OK
	{
		if (access(tmp_stock[i], F_OK) == 0)
			return (tmp_stock[i]);
		i++;
	}
	// char *tmp = ft_strjoin("./", cmd_name);
	// if (access(tmp, F_OK) == 0)
	// 	return (tmp);
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
	{
		/*
		 if the user did not give the absolute path add it.
		 in case of cmd not found it will return the same name without path and change the flag to cmd not found
		*/
		cmd->cmd = get_full_path(stock, token->arg, &cmd->cmd_not_found);
	}
	else
	{
		/*
		 the user entred a cmd wih the absolute path.
		*/
		cmd->cmd = token->arg;
		//if (check_for_err(cmd) == -1)
		//	return (-1);
	}
	// this condition handle enmpty strings as cmd: "" or ''
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
//	int	i;
//	int	len;
	char	*heredoc_name;
	t_heredoc	*heredoc_node;

//	len = 0;
//	i = 0;
	(void)data;
	heredoc_node = ft_collector(sizeof(t_heredoc), ALLOC);
	heredoc_node->heredoc_del = token->arg;
	heredoc_name = ft_strjoin("heredoc", read_rand());
	heredoc_name = ft_strjoin("/tmp/", heredoc_name);
	heredoc_node->heredoc_file = heredoc_name;
	heredoc_node->expand = 1;
	if (token->is_dquote || token->is_squote)
		heredoc_node->expand = 0;
		//return (perror("minishell"), -1);
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
	node->STDIN = 0;
	node->STDOUT = 1;
	node->next = NULL;
}


int	empty_env_var(t_token *current)
{
	if (current->is_env_var && !is_redir(current) && !current->prev && !current->next && !current->is_dquote && !current->arg[0])
		return (1);
	return (0);
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
		if (current->is_heredoc == HEREDOC)
			handle_heredoc(node, current, data);

		else if(flag && (current->is_dquote
				|| current->is_word
				|| current->is_squote
				|| current->is_env_var)
				&& !(current->is_env_var
				&& !current->is_dquote
				&& !current->arg[0])
				&& !is_redir(current)
				&& !current->is_ambiguous)
		{
			flag = 0;
			if (set_cmd_name(node, current, data) == -1)
				node->should_not_execute = 1;
		}
		else if (!(current->is_env_var && !current->arg[0] && !current->is_dquote)
				&& !current->is_ambiguous
				&& !is_redir(current))
			add_to_argv(node, current);
		current = current->next;
	}
	if (node->cmd && !ft_strcmp("ls", get_cmd_name(node->argv[0])))
		node->argv = realloc_argv(node->argv);
	add_cmd(cmd_list, node);
}

t_cmd	*exec_setup(void	**stock, t_data *data)
{
	t_cmd	*cmd_list;
	int	i;

	i = 0;
	cmd_list = NULL;
	while (stock[i])
	{
		cmd_builder(&cmd_list, (t_token *)stock[i], data);
		i++;
	}
	return (cmd_list);
}


void    pretty_print_cmd_list(t_cmd *cmd_list)
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

    // Traverse the linked list of commands
    while (cmd_list)
    {
        printf("\n.---------------------------------------.\n");
        printf("|               COMMAND %-3d             |\n", cmd_num++);
        printf(":---------------------------------------:\n");

        // Print the full command path
        printf("| %-12s: %s\n", "Command", cmd_list->cmd ? cmd_list->cmd : "(null)");
        printf(":---------------------------------------:\n");

        // Print the arguments (argv)
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

        // Print I/O file descriptors
        printf("| %-12s: %d\n", "STDIN", cmd_list->STDIN);
        printf("| %-12s: %d\n", "STDOUT", cmd_list->STDOUT);
        printf(":---------------------------------------:\n");
        
        // --- NEW SECTION for flags ---
        printf("| %-19s: %d\n", "Cmd Not Found Flag", cmd_list->cmd_not_found);
        printf("| %-19s: %d\n", "Should Not Execute Flag", cmd_list->should_not_execute); // Print as a positive condition
        printf(":---------------------------------------:\n");


        // Print heredoc list
        t_heredoc *current_heredoc = cmd_list->heredcs;
        if (current_heredoc)
        {
            int heredoc_num = 1;
            // Loop through each heredoc associated with this command
            while (current_heredoc)
            {
                printf("| Heredoc #%-2d\n", heredoc_num++);
                printf("|   %-10s: [%s]\n", "Delimiter", current_heredoc->heredoc_del ? current_heredoc->heredoc_del : "(null)");
                printf("|   %-10s: [%s]\n", "File", current_heredoc->heredoc_file ? current_heredoc->heredoc_file : "(null)");
                printf("|   %-10s: %d\n", "FD", current_heredoc->fd);
                
                current_heredoc = current_heredoc->next;
                // Add a sub-divider if there is another heredoc to print
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

        // Move to the next command in the list
        cmd_list = cmd_list->next;
    }
}
