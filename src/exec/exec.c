/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:34:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/20 22:44:56 by slasfar          ###   ########.fr       */
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
		current->stdin_ = open(current->last_heredoc->heredoc_file,
				O_RDONLY, 0644);
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
			printf("%d Segmentation fault (core dumped) %s",
				pid, last->argv[0]);
		else if (WTERMSIG(status) == SIGTERM)
			printf("%s terminated", last->argv[0]);
		else if (WIFSTOPPED(status))
		{
			data->last_exit_code = 128 + WSTOPSIG(status);
		}
		write(2, "\n", 1);
	}
}

void	close_cmd_fds(t_cmd *current)
{
	if (current->stdin_ != 0)
		close(current->stdin_);
	if (current->stdout_ != 1)
		close(current->stdout_);
}

void	do_multiple_child(t_data *data, t_cmd *current, int fd[2])
{
	set_to_default();
	if (current->next)
		dup2(fd[1], STDOUT_FILENO);
	should_use_last_herdoc(current);
	change_std(current, data);
	close_pipe(fd);
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

void	do_while_pipes(t_data *data, t_cmd *current, int fd[2], int *pid)
{
	pipe(fd);
	signal(SIGINT, SIG_IGN);
	*pid = fork();
	if (*pid == 0)
		do_multiple_child(data, current, fd);
	dup2(fd[0], STDIN_FILENO);
	close_pipe(fd);
	close_cmd_fds(current);
}

// had function khasna ngado leha nrom wn9essemoha asap!!
void	multiple_pipes(t_data *data, t_cmd *cmd_list)
{
	t_cmd	*current;
	pid_t	*pid_list;
	int		len;
	int		fd[2];
	pid_t	pid;

	current = cmd_list;
	pid_list = NULL;
	len = 0;
	while (current)
	{
		do_while_pipes(data, current, fd, &pid);
		add_pid(&pid_list, pid, &len);
		if (!current->next)
			break ;
		current = current->next;
	}
	dup2(data->stdin_, STDIN_FILENO);
	save_exit_status(current, data, pid);
	pid = 0;
	if (len > 1)
	{
		while (pid < (len - 1))
			waitpid(pid_list[pid++], NULL, WUNTRACED);
	}
}

void	do_single_child(t_data *data, t_cmd *cmd)
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

void	single_command(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	if (ft_builtin(cmd) == 0)
	{
		pid = fork();
		if (pid == 0)
			do_single_child(data, cmd);
		close_cmd_fds(cmd);
		save_exit_status(cmd, data, pid);
	}
}

void	execute(t_cmd *cmd_list, t_data *data)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmd_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	if (count > 1)
		multiple_pipes(data, cmd_list);
	else
		single_command(data, cmd_list);
}
