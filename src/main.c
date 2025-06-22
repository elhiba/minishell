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
		// ft_parse(&data);
		full_execution(&data);
	}
	return (0);
}

// grep -> hi ->  infile -> outfile -> null
	
// int	handle_heredoc(char *delim)
// {

// }

int	resolve_redirections(t_data *data, t_cmd *cmd)
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
			// if (tmp->red_type == RED_HERE)
			// 	cmd->in_fd = handle_heredoc(tmp->arg);
			if (cmd->in_fd == -1 || cmd->out_fd == -1)
				return (perror(tmp->arg), cmd->skip_cmd = 1, data->last_exit_code = 1);
			if (tmp->red_type != 0)
				remove_token(&cmd->list, tmp);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
	return (1);
}

void	exec_single_builtin(t_data *data, t_cmd *cmd)
{
	int	in_save;
	int	out_save;

	in_save = dup(0);
	out_save = dup(1);
	if (cmd->in_fd != 0)
		dup2(cmd->in_fd, 0);
	if (cmd->out_fd != 1)
		dup2(cmd->out_fd, 1);
	do_builtin(data, cmd->list, 0);
	dup2(in_save, 0);
	dup2(out_save, 1);
	close(in_save);
	close(out_save);
}

void	full_execution(t_data *data)
{
	int		last_pid;
	t_cmd	*cmd;

	cmd = data->cmd_list;
	resolve_redirections(data, cmd);
	if (is_builtin(cmd->list) && !cmd->next && !cmd->skip_cmd)
		exec_single_builtin(data, cmd);
	else
	{
		while (cmd)
		{
			if (cmd->skip_cmd)
			{
				cmd = cmd->next;
				continue ;
			}
			last_pid = fork();
			if (last_pid == 0)
			{
				dup2(cmd->in_fd, 0);
				dup2(cmd->out_fd, 1);
				if (is_builtin(cmd->list))
					do_builtin(data, cmd->list, 1);
				else
					execute_cmd(data, cmd->list);
			}
			if (last_pid > 0)
				wait(&data->last_exit_code);
			cmd = cmd->next;
		}
		while (wait(NULL) > 0)
			;
		// if (WIFEXITED(status))
		// 	data->last_exit_code = WEXITSTATUS(status);
		// else if (WIFSIGNALED(status))
		// 	data->last_exit_code = 128 + WTERMSIG(status);
	}
	free_cmd_list(&data->cmd_list);
}

// void	execute_cmd(t_data *data, t_token *list)
// {
// 	char	*cmd;
// 	char	**argv;		

// 	cmd = check_in_path(list, data);
// 	argv = build_argv(data, list);
// 	if (execve(cmd, argv, data->env) == -1)
// 	{
// 		if (ft_strchr(cmd, '/'))
// 			printf("%s: No such file or directory\n", cmd);
// 		else
// 			printf("%s: command not found\n", cmd);
// 		free(argv);
// 		full_cleanup(data);
// 		exit(127);
// 	}	
// }
