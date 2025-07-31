/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:12:36 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/31 20:08:32 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_redir(t_token *current)
{
	if (current->is_infile || current->is_outfile
		|| current->is_append || current->is_heredoc)
		return (true);
	return (false);
}

int	check_redir_err(t_token *current, t_data *data)
{
	if (current->is_ambiguous)
		return (data->last_exit_code = 1,
			error_execution(current->ambiguous_name, NULL, IS_SUS), -1);
	if (!current->arg[0])
		return (data->last_exit_code = 1,
			error_execution(current->arg, NULL, NOR_FILE_DIREC), -1);
	if (is_a_directory(current->arg) && !current->is_infile)
		return (data->last_exit_code = 1,
			error_execution(current->arg, NULL, IS_DIR), -1);
	return (0);
}

int	infile_norm(t_cmd *cmd, t_token *token, t_data *data)
{
	if (cmd->stdin_ != 0)
		close(cmd->stdin_);
	if (is_a_directory(token->arg) && token->next)
		return (0);
	cmd->use_last_heredoc = 0;
	cmd->stdin_ = open(token->arg, O_RDONLY, 0644);
	cmd->stdin_s = token->arg;
	if (cmd->stdin_ == -1)
		return (data->last_exit_code = 1,
			error_execution(token->arg, strerror(errno), -1), -1);
	close(cmd->stdin_);
	return (0);
}

int	outfile_norm(t_cmd *cmd, t_token *token, t_data *data)
{
	if (cmd->stdout_ != 1)
		close(cmd->stdout_);
	cmd->stdout_ = open(token->arg, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	cmd->stdout_s = token->arg;
	if (cmd->stdout_ == -1)
		return (data->last_exit_code = 1,
			error_execution(token->arg, strerror(errno), -1), -1);
	close(cmd->stdout_);
	return (0);
}

int	set_fd(t_cmd *cmd, t_token *token, t_data *data)
{
	if (token->is_infile == INPUT_FILE)
	{
		if (infile_norm(cmd, token, data) == -1)
			return (-1);
	}
	else if (token->is_outfile == OUTPUT_FILE)
	{
		if (outfile_norm(cmd, token, data) == -1)
			return (-1);
	}
	else if (token->is_append == APPEND)
	{
		if (cmd->stdout_ != 1)
			close(cmd->stdout_);
		cmd->stdout_ = open(token->arg, O_CREAT | O_WRONLY | O_APPEND, 0644);
		cmd->stdout_s = token->arg;
		if (cmd->stdout_ == -1)
			return (data->last_exit_code = 1,
				error_execution(token->arg, strerror(errno), -1), -1);
		close(cmd->stdout_);
	}
	return (0);
}
