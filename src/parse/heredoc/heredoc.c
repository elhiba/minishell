/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:53:22 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/20 16:00:10 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	heredoc_handler(int sig)
{
	t_cmd		*cmd;
	t_heredoc	*heredocs;

	(void)sig;
	cmd = save_cmd(NULL);
	heredocs = save_heredoc(NULL);
	close(heredocs->fd);
	if (cmd->stdin_ != 0)
		close(cmd->stdin_);
	if (cmd->stdout_ != 1)
		close(cmd->stdout_);
	close(cmd->data->stdin_);
	close(cmd->data->stdout_);
	ft_collector(0, FREE);
	write(2, "\n", 1);
	exit(130);
}

static void	heredoc_logic(t_cmd *cmd, t_heredoc *heredoc)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
		heredoc_input(heredoc, cmd->data);
		if (cmd->stdin_ != 0)
			close(cmd->stdin_);
		if (cmd->stdout_ != 1)
			close(cmd->stdout_);
		close(cmd->data->stdin_);
		close(cmd->data->stdout_);
		ft_collector(0, FREE);
		exit(0);
	}
	waitpid(pid, &status, WUNTRACED);
	heredoc_exit_code(status, cmd->data, pid);
}

void	heredoc(t_cmd *cmd_list)
{
	t_cmd		*cmd;
	t_heredoc	*heredocs;

	cmd = cmd_list;
	prevent_flag(1337);
	while (cmd)
	{
		save_cmd(cmd);
		if (cmd->heredcs)
		{
			heredocs = cmd->heredcs;
			while (heredocs && !prevent_flag(42))
			{
				save_heredoc(heredocs);
				heredoc_logic(cmd, heredocs);
				cmd->last_heredoc = heredocs;
				heredocs = heredocs->next;
			}
			if (prevent_flag(42))
				prevent_exec(cmd_list);
		}
		cmd = cmd->next;
	}
}
