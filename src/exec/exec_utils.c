/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:12:55 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/31 21:06:11 by moel-hib         ###   ########.fr       */
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
		current->stdin_s = current->last_heredoc->heredoc_file;
	}
}

void	change_std(t_cmd *current, t_data *data)
{
	close(data->stdin_);
	close(data->stdout_);
	if ((current->should_not_execute
			|| current->cmd_not_found) && !current->cmd)
		return ;
	if (current->stdin_s != NULL)
	{
		current->stdin_ = open(current->stdin_s, O_RDONLY, 0644);
		dup2(current->stdin_, STDIN_FILENO);
		close(current->stdin_);
	}
	if (current->stdout_s != NULL)
	{
		current->stdout_ = open(current->stdout_s, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		dup2(current->stdout_, STDOUT_FILENO);
		close(current->stdout_);
	}
}

void	close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

void	close_cmd_fds(t_cmd *current)
{
	if ((current->should_not_execute
			|| current->cmd_not_found) && !current->cmd)
		return ;
	if (current->stdin_ != 0)
		close(current->stdin_);
	if (current->stdout_ != 1)
		close(current->stdout_);
}
