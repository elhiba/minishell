/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:12:50 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/21 11:14:08 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
