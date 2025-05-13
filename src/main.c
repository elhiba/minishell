/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:59:49 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/01 17:54:57 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// fix this later on
char	*build_prompt(t_data *data)
{
	char	cwd[1000];
	char	*prompt;

	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, ft_getenv("PWD", data),1000);
	prompt = malloc(1000);
	if (!prompt)
		return (NULL);
	snprintf(prompt, 10000,
		"┌──(minishell)-[%s]\n└─❯ ", cwd);
	return (prompt);
}

// fix this later on
volatile sig_atomic_t	g_received_signal = 0;

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*prompt;

	(void) ac;
	(void) av;
	ft_bzero(&data, sizeof(data));
	data.env = copy_env(env);
	handle_signals();
	while (1)
	{
		prompt = build_prompt(&data);
		data.readline_in = readline(prompt);
		// fix this later on
		if (g_received_signal == SIGINT)
		{
			data.last_exit_code = 130;
			g_received_signal = 0;
		}
		free(prompt);
		if (data.readline_in == NULL)
		{
			printf("exit\n");
			free_d_arr(data.env);
			exit(EXIT_SUCCESS);
		}
		add_history(data.readline_in);
		ft_parse(&data);
		if (!is_builtin(&data) && data.token_list)
			execute_cmd(&data);
		else
			free_token_list(&(data.token_list));
	}
	return (0);
}

// grep -> hi ->  infile -> outfile -> null

int	handle_heredoc(char *delim)
{

}

void	remove_token(t_token **head, t_token *node)
{
	if (!node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	else
		*head = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->arg);
	free(node);
}

int	resolve_redirections(t_cmd *cmd)
{
	t_token	*tmp;

	while (cmd)
	{
		tmp = cmd->list;
		while (tmp)
		{
			if (tmp->red_type == RED_IN)
				cmd->in_fd = open(tmp->arg, O_RDONLY);
			if (tmp->red_type == RED_OUT)
				cmd->out_fd = open(tmp->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (tmp->red_type == RED_APP)
				cmd->out_fd = open(tmp->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (tmp->red_type == RED_HERE)
				cmd->in_fd = handle_heredoc(tmp->arg);
			if (tmp->red_type != 0 && (cmd->in_fd == -1 || cmd->out_fd == -1))
				return (perror(tmp->arg), cmd->skip_cmd = 1);
			if (tmp->red_type != 0)
				remove_token(&cmd->list, tmp);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
}

void	full_exec(t_data *data)
{
	int		last_pid;
	int		i;

	i = 0;
	resolve_redirections(data->cmd_list);
	if (data->cmd_list->list == NULL && is_builtin(data))
		do_builtin(data);	
	else
	{
		while (data->cmd_list)
		{
			if (data->cmd_list->skip_cmd == 1)
				continue ;
			last_pid = fork();
			if (last_pid == 0)
			{
				dup2(data->cmd_list->in_fd, 0);
				dup2(data->cmd_list->out_fd, 1);
				if (is_builtin(data))
					do_builtin
				else
					execute_cmd(data);
			}
			if (last_pid > 0)
				wait(&data->last_exit_code);
			i++;
		}
		while (wait(NULL) > 0)
			;
	}
}
void	execute_cmd(t_data *data)
{
	int		status;
	pid_t	pid_child;
	char	*cmd;
	char	**argv;

	status = 0;
	cmd = check_in_path(data->token_list, data);
	argv = build_argv(data, data->token_list);
	pid_child = fork();
	if (pid_child > 0)
		wait(&status);
	if (pid_child == 0)
	{
		if (execve(cmd, argv, data->env) == -1)
		{
			if (ft_strchr(cmd, '/'))
				printf("%s: No such file or directory\n", cmd);
			else
				printf("%s: command not found\n", cmd);
			free(argv);
			free_token_list(&data->token_list);
			free_d_arr(data->env);
			exit(127);
		}
		(free(argv), error_handler(cmd, data));
	}
	if (WIFEXITED(status))
		data->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->last_exit_code = 128 + WTERMSIG(status);
	free_token_list(&data->token_list);
	free(argv);
}
