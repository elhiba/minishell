/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:52:09 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/21 12:24:55 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	heredoc_input(t_heredoc *heredoc, t_data *data)
{
	char	*buffer;
	char	*managed_buffer;

	heredoc->fd = open(heredoc->heredoc_file, O_CREAT | O_WRONLY, 0644);
	while (1)
	{
		buffer = readline("> ");
		if (!buffer)
		{
			write_heredoc_warning(heredoc);
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

void	signal_term(int signal, pid_t pid)
{
	char	*tmp;

	tmp = ft_itoa(pid);
	if (signal == SIGSEGV)
	{
		tmp = ft_strjoin(tmp,
				"Segmentation fault (core dumped) HEREDOC\n");
		write(2, tmp, ft_strlen(tmp));
	}
	else if (signal == SIGTERM)
	{
		tmp = ft_strjoin(tmp,
				"terminated HEREDOC\n");
		write(2, tmp, ft_strlen(tmp));
	}
}

void	heredoc_exit_code(int status, t_data *data
	, pid_t pid)
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
		signal_term(WTERMSIG(status), pid);
	}
	else if (WIFSTOPPED(status))
		data->last_exit_code = 128 + WSTOPSIG(status);
}

t_heredoc	*save_heredoc(t_heredoc *heredocs)
{
	static t_heredoc	*saved_heredoc;

	if (heredocs == NULL)
		return (saved_heredoc);
	else
	{
		saved_heredoc = heredocs;
		return (saved_heredoc);
	}
}

t_cmd	*save_cmd(t_cmd *cmd)
{
	static t_cmd	*saved_cmd;

	if (cmd == NULL)
		return (saved_cmd);
	else
	{
		saved_cmd = cmd;
		return (saved_cmd);
	}
}
