/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:53:22 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/17 13:48:10 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}

void	prevent_exec(t_cmd *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	while (cmd)
	{
		cmd->should_not_execute = 1;
		cmd = cmd->next;
	}
}

static int	prevent_flag(int sigint_was_here)
{
	static int	i;

	if (sigint_was_here == 2)
	{
		i = 2;
		return (i);
	}
	else if (sigint_was_here == 1337)
	{
		i = 0;
		return(i);
	}
	else
		return (i);
}

static void	heredoc_input(t_heredoc *heredoc, t_data *data)
{
	char	*buffer;
	char	*managed_buffer;

	heredoc->fd = open(heredoc->heredoc_file, O_CREAT | O_WRONLY, 0644);
	while (1)
	{
		buffer = readline("> ");
		if (!buffer)
		{
			printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", heredoc->heredoc_del);
			break ;
		}
		if (!ft_strcmp(buffer, heredoc->heredoc_del))
		{
			free(buffer);
			break ;
		}
		managed_buffer = ft_strdup(buffer);
		free(buffer);
		if (is_it_expandable(managed_buffer) && heredoc->expand)
			expand_variable_heredoc(data, data->env, &managed_buffer);
		ft_putendl_fd(managed_buffer, heredoc->fd);
	}
	close(heredoc->fd);
}

static void	signal_term(int signal, pid_t pid, t_cmd *cmd_list)
{
	if (signal == SIGSEGV)
		printf("%d Segmentation fault (core dumped) HEREDOC", pid);
	else if (signal == SIGTERM)
		printf("%d terminated HEREDOC", pid);
	prevent_exec(cmd_list);
	write(2, "\n", 1);
}

static void	heredoc_exit_code(int status, t_data *data, pid_t pid, t_cmd *cmd_list)
{
	if (WIFEXITED(status))
	{
		data->last_exit_code = WEXITSTATUS(status);
		if (data->last_exit_code == 130)
			prevent_flag(2);
	}
	else if (WIFSIGNALED(status))
	{
		data->last_exit_code = 128 + WTERMSIG(status);
		signal_term(WTERMSIG(status), pid, cmd_list);
	}
	else if (WIFSTOPPED(status))
		data->last_exit_code = 128 + WSTOPSIG(status);
}

static t_heredoc	*save_heredoc(t_heredoc *heredocs)
{
	static t_heredoc *saved_heredoc;

	if (heredocs == NULL)
		return (saved_heredoc);
	else
	{
		saved_heredoc = heredocs;
		return (saved_heredoc);
	}
}

static t_cmd	*save_cmd(t_cmd *cmd)
{
	static t_cmd *saved_cmd;

	if (cmd == NULL)
		return (saved_cmd);
	else
	{
		saved_cmd = cmd;
		return (saved_cmd);
	}
}

void heredoc_handler(int sig)
{
	t_cmd		*cmd;
	t_heredoc	*heredocs;

	(void)sig;
	cmd = save_cmd(NULL);
	heredocs = save_heredoc(NULL);
	close(heredocs->fd);
	if (cmd->STDIN != 0)
			close(cmd->STDIN);
	if (cmd->STDOUT != 1)
		close(cmd->STDOUT);
	close(cmd->data->STDIN);
	close(cmd->data->STDOUT);
	ft_collector(0, FREE);
	write(2, "\n", 1);
	exit(130);
}


static void	heredoc_logic(t_cmd *cmd, t_heredoc *heredoc, t_cmd *cmd_list)
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
		if (cmd->STDIN != 0)
			close(cmd->STDIN);
		if (cmd->STDOUT != 1)
			close(cmd->STDOUT);
		close(cmd->data->STDIN);
		close(cmd->data->STDOUT);
		ft_collector(0, FREE);
		exit(0);
	}
	waitpid(pid, &status, WUNTRACED);
	heredoc_exit_code(status, cmd->data, pid, cmd_list);
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
				heredoc_logic(cmd, heredocs, cmd_list);
				cmd->last_heredoc = heredocs;
				heredocs = heredocs->next;
			}
			if (prevent_flag(42))
				prevent_exec(cmd_list);
		}
		cmd = cmd->next;
	}
}
