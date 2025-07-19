/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:34:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/19 09:12:20 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_pid(pid_t **pid, pid_t new_pid, int *size)
{
	pid_t	*new_pid_list;
	int		i;

	i = 0;
	new_pid_list = ft_collector(sizeof(pid_t) * (*size + 1), ALLOC);
	while (i < *size)
	{
		new_pid_list[i] = (*pid)[i];
		i++;
	}
	new_pid_list[i] = new_pid;
	*size += 1;
	*pid = new_pid_list;

}

void	should_use_last_herdoc(t_cmd *current)
{
	if (current->last_heredoc && current->use_last_heredoc)
	{
		if (current->stdin_ != 0)
			close(current->stdin_);
		current->stdin_ = open(current->last_heredoc->heredoc_file, O_RDONLY, 0644);
	}
}

void	change_std(t_cmd *current, t_data *data)
{
	if (current->stdin_ != 0)
	{
		dup2(current->stdin_, STDIN_FILENO);
		close(current->stdin_);
	}
	if (current->stdout_ != 1)
	{
		dup2(current->stdout_, STDOUT_FILENO);
		close(current->stdout_);
	}
	close(data->stdin_);
	close(data->stdout_);
}

void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	save_exit_status(t_cmd *last, t_data *data, pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		data->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		data->last_exit_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGSEGV)
			printf("%d Segmentation fault (core dumped) %s", pid, last->argv[0]);
		else if (WTERMSIG(status) == SIGTERM)
			printf("%s terminated", last->argv[0]);
		else if (WIFSTOPPED(status))
		{
			data->last_exit_code = 128 + WSTOPSIG(status);
		}
		write(2, "\n", 1);
	}
}

// had function khasna ngado leha nrom wn9essemoha asap!!
void	multiple_pipes(t_data *data, t_cmd *cmd_list)
{
	t_cmd *current = cmd_list;
	pid_t	*pid_list;
	int		len = 0;
	t_cmd *last = NULL;
	int	fd[2];
	pid_t pid;

	current = cmd_list;
	while (current)
	{
		pipe(fd);
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == 0)
		{
			set_to_default();
			if (current->next)
			{
				dup2(fd[1], STDOUT_FILENO);
			}
			should_use_last_herdoc(current);
			change_std(current, data);
			close_pipe(fd);
			close(data->stdin_);
			close(data->stdout_);
			if (current->should_not_execute || current->cmd_not_found)
			{
				ft_collector(0, FREE);
				exit(data->last_exit_code);
			}
			if (!current->cmd)
				ft_collector(0, EXIT);
			if (ft_builtin(current) == 0)
			{
				execve(current->cmd, current->argv, data->env);
				printf("minishell: %s: %s\n", current->argv[0], strerror(errno));
				ft_collector(0, FREE);
				if (errno == ENOENT)
					exit(127);
				else
					exit (126);
			}
			ft_collector(0, FREE);
			exit(data->last_exit_code);
		}
		add_pid(&pid_list, pid, &len);
		dup2(fd[0], STDIN_FILENO);
		close_pipe(fd);
		last = current;
		if (current->stdin_ != 0)
			close(current->stdin_);
		if (current->stdout_ != 1)
			close(current->stdout_);
		current = current->next;
	}
	dup2(data->stdin_, STDIN_FILENO);
	save_exit_status(last, data, pid);
	pid = 0;
	if (len > 1)
	{
		while (pid < len)
			waitpid(pid_list[pid++], NULL, WUNTRACED);
	}
}


void	single_command(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	if (ft_builtin(cmd) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			set_to_default();
			should_use_last_herdoc(cmd);
			change_std(cmd, data);
			if (cmd->should_not_execute || cmd->cmd_not_found)
			{
				ft_collector(0, FREE);
				exit(data->last_exit_code);
			}
			if (!cmd->cmd)
				ft_collector(0, EXIT);
			execve(cmd->cmd, cmd->argv, data->env);
			printf("minishell: %s: %s\n", cmd->argv[0], strerror(errno));
			ft_collector(0, FREE);
			if (errno == ENOENT)
				exit(127);
			else
				exit (126);
		}
		if (cmd->stdin_ != 0)
			close(cmd->stdin_);
		if (cmd->stdout_ != 1)
			close(cmd->stdout_);
		save_exit_status(cmd, data, pid);
	}
}

void	execute(t_cmd *cmd_list, t_data *data)
{
	int	count;
	t_cmd	*current;

	count = 0;
	current = cmd_list;
	while(current)
	{
		count++;
		current = current->next;
	}
	if (count > 1)
		multiple_pipes(data, cmd_list);
	else
		single_command(data, cmd_list);
}

//char	*join_path(const char *dir, const char *cmd)
//{
//	char	*tmp;
//	char	*full_path;
//
//	tmp = ft_strjoin(dir, "/");
//	full_path = ft_strjoin(tmp, cmd);
//	free(tmp);
//	return (full_path);
//}
//
//char	*check_in_path(t_token *list, t_data *data)
//{
//	char	*cmd;
//	char	*full_cmd;
//	char	**dirs;
//	int		i;
//
//	cmd = list->arg;
//	if (access(cmd, X_OK) == 0)
//		return (cmd);
//	dirs = ft_split(ft_getenv("PATH", data), ':');
//	if (!dirs)
//		error_handler("path malloc error", NULL);
//	i = 0;
//	while (dirs[i])
//	{
//		full_cmd = join_path(dirs[i], cmd);
//		if (access(full_cmd, X_OK) == 0)
//		{
//			list->arg = full_cmd;
//			return (full_cmd);
//		}
//		i++;
//	}
//	return (cmd);
//}
//
//char	**build_argv(t_data *data, t_token *tokens)
//{
//	char	**argv;
//	int		count;
//	int		i;
//	t_token	*tmp;
//
//	count = 0;
//	tmp = tokens;
//	while (tmp)
//	{
//		count++;
//		tmp = tmp->next;
//	}
//	argv = malloc(sizeof(char *) * (count + 1));
//	if (!argv)
//		error_handler("Malloc failed", data);
//	i = 0;
//	while (tokens)
//	{
//		argv[i] = tokens->arg;
//		tokens = tokens->next;
//		i++;
//	}
//	argv[i] = NULL;
//	return (argv);
//}
//
//void	ft_execution(t_data *data)
//{
//	int		status;
//	pid_t	pid_child;
//	char	*cmd;
//	char	**argv;
//
//	status = 0;
//	cmd = check_in_path(data->token_list, data);
//	argv = build_argv(data, data->token_list);
//	pid_child = fork();
//	if (pid_child > 0)
//		wait(&status);
//	if (pid_child == 0)
//	{
//		if (execve(cmd, argv, data->env) == -1)
//		{
//			if (ft_strchr(cmd, '/'))
//				printf("%s: No such file or directory\n", cmd);
//			else
//				printf("%s: command not found\n", cmd);
//			exit(127);
//		}
//		(error_handler(cmd, data));
//	}
//	if (WIFEXITED(status))
//		data->last_exit_code = WEXITSTATUS(status);
//	else if (WIFSIGNALED(status))
//		data->last_exit_code = 128 + WTERMSIG(status);
//}
