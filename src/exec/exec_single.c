/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:12:48 by slasfar           #+#    #+#             */
/*   Updated: 2025/08/02 16:28:06 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strchr_(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	remove_var_without_equal_sign(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (ft_strchr_(data->env[i], '='))
		{
			data->env[j] = data->env[i];
			j++;
		}
		i++;
	}
	data->env[j] = NULL;
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
	remove_var_without_equal_sign(data);
	execve(cmd->cmd, cmd->argv, data->env);
	error_execution(cmd->cmd, strerror(errno), 1337);
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
