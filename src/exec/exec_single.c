/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:12:48 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/31 17:30:45 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	do_single_child(t_data *data, t_cmd *cmd)
{
	set_to_default();
	if (cmd->should_not_execute || cmd->cmd_not_found)
	{
		ft_collector(0, FREE);
		exit(data->last_exit_code);
	}
	if (!cmd->cmd)
		ft_collector(0, EXIT);
	change_std(cmd, data);
	should_use_last_herdoc(cmd);
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
