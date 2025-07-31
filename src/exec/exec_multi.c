/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:12:42 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/31 17:11:24 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
