/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:12:55 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/21 11:14:11 by slasfar          ###   ########.fr       */
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

void	close_cmd_fds(t_cmd *current)
{
	if (current->stdin_ != 0)
		close(current->stdin_);
	if (current->stdout_ != 1)
		close(current->stdout_);
}
