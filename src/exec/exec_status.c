/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:12:50 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/21 12:49:32 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_code(int signal, pid_t pid, t_cmd *last, int status)
{
	char	*tmp;

	tmp = ft_itoa(pid);
	if (signal == SIGSEGV)
	{
		tmp = ft_strjoin3(tmp,
				" Segmentation fault (core dumped) ",
				last->argv[0]);
		write(2, tmp, ft_strlen(tmp));
	}
	else if (signal == SIGTERM)
	{
		tmp = ft_strjoin3(tmp,
				"terminated ", last->argv[0]);
		write(2, tmp, ft_strlen(tmp));
	}
	else if (WIFSTOPPED(status))
	{
		last->data->last_exit_code = 128 + WSTOPSIG(status);
	}
	write(2, "\n", 1);
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
		signal_code(WTERMSIG(status), pid, last, status);
	}
}
