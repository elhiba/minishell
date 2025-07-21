/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:52:19 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/21 03:44:51 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	is_a_directory(char *cmd)
{
	struct stat statbuf;

	ft_bzero(&statbuf, sizeof(statbuf));
	if (!stat(cmd, &statbuf)&& S_ISDIR(statbuf.st_mode))
		return (1);
	return (0);
}

typedef	enum s_err
{
	IS_DIR,
	PERM_DENY,
	NOR_FILE_DIREC,
	IS_SUS
} t_err;

int	error_execution(char *arg, char *erroname, t_err flag)
{
	char	*buff;

	buff = 0;
	if (flag == IS_DIR)
		buff = ft_strjoin3(PRG_NAME, arg, ": Is a directory\n");
	else if (flag == PERM_DENY)
		buff = ft_strjoin3(PRG_NAME, arg, ": Permission denied\n");
	else if (flag == NOR_FILE_DIREC)
		buff = ft_strjoin3(PRG_NAME, arg, ": No such file or directory\n");
	else if (flag == IS_SUS)
		buff = ft_strjoin3(PRG_NAME, arg, ": Is SuS\n");
	else
		buff = ft_strjoin3(PRG_NAME, arg,
				ft_strjoin(" ", ft_strjoin(erroname, "\n")));

	return (write(2, buff, ft_strlen(buff)));
}

/*
	if (cmd->cmd && access(cmd->cmd, F_OK) != 0)
	return (cmd->data->last_exit_code = 127, printf("minishell: %s: No such file or directory\n", cmd->cmd), -1); */
int	check_for_err(t_cmd *cmd)
{
	if (is_a_directory(cmd->cmd))
		return (cmd->data->last_exit_code = 126,
		error_execution(cmd->argv[0], NULL, IS_DIR), -1);
	else if (access(cmd->cmd, F_OK) == 0)
	{
		if (access(cmd->cmd, X_OK) != 0)
			return (cmd->data->last_exit_code = 126,
		error_execution(cmd->argv[0], NULL, PERM_DENY), -1);
	}
	return (0);
}

bool	is_redir(t_token *current)
{
	if (current->is_infile || current->is_outfile
		|| current->is_append || current->is_heredoc)
		return (true);
	return (false);
}

bool	is_a_fifo(char *str)
{
	struct stat statbuf;

	ft_bzero(&statbuf, sizeof(statbuf));
	stat(str, &statbuf);
	if (S_ISFIFO(statbuf.st_mode))
		return (1);
	return (0);
}

/*
	if (is_a_fifo(current->arg))
	 	return (data->last_exit_code = 1, printf("minishell: %s: hada kaytsema tmekrib\n", current->arg), -1);
	if (current->is_infile && access(current->arg, F_OK) != 0)
		return (printf("minishell: %s: No such file or directory\n", current->arg), -1);
*/
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

int	set_fd(t_cmd *cmd, t_token *token, t_data *data)
{
	if (token->is_infile == INPUT_FILE)
	{
		if (cmd->stdin_ != 0)
			close(cmd->stdin_);
		if (is_a_directory(token->arg) && token->next)
			return (0);
		cmd->use_last_heredoc = 0;
		cmd->stdin_ = open(token->arg, O_RDONLY, 0644);
		if (cmd->stdin_ == -1)
			return (data->last_exit_code = 1,
			error_execution(token->arg, strerror(errno), -1), -1);
	}
	else if (token->is_outfile == OUTPUT_FILE)
	{
		if (cmd->stdout_ != 1)
			close(cmd->stdout_);
		cmd->stdout_ = open(token->arg, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd->stdout_ == -1)
			return (data->last_exit_code = 1,
			error_execution(token->arg, strerror(errno), -1), -1);
	}
	else if (token->is_append == APPEND)
	{
		if (cmd->stdout_ != 1)
			close(cmd->stdout_);
		cmd->stdout_ = open(token->arg, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (cmd->stdout_ == -1)
			return (data->last_exit_code = 1,
			error_execution(token->arg, strerror(errno), -1), -1);
	}
	return (0);
}

int	check_and_set_fd(t_cmd *cmd_current, t_token *token_current)
{
	while (token_current)
	{
		if (is_redir(token_current))
		{
			if (!token_current->is_heredoc && check_redir_err(token_current, cmd_current->data) == -1)
			{
				cmd_current->should_not_execute = 1;
				cmd_current->exit_code = cmd_current->data->last_exit_code;
				return (1);
			}
			else if (!token_current->is_heredoc && set_fd(cmd_current, token_current, cmd_current->data) == -1)
			{
				cmd_current->should_not_execute = 1;
				cmd_current->exit_code = cmd_current->data->last_exit_code;
				return (1);
			}
			else if (token_current->is_heredoc)
			{
				cmd_current->use_last_heredoc = 1;
			}
		}
		token_current = token_current->next;
	}
	return (0);
}


int	check_cmd_errors(t_cmd *cmd_current, t_token *token_current)
{
	while (cmd_current->cmd && token_current && !cmd_current->should_not_execute)
	{
		if (cmd_current->cmd_not_found)
		{
			if (!cmd_current->cmd[0])
				write(2, ft_strjoin3("minishell: \'",
					cmd_current->cmd, "\': command not found!\n"),
					ft_strlen(cmd_current->cmd) + 34);
			else
				write(2, ft_strjoin(cmd_current->cmd,
					": command not found!\n"),
					ft_strlen(cmd_current->cmd) + 21);
			cmd_current->data->last_exit_code = 127;
			cmd_current->exit_code = cmd_current->data->last_exit_code;
			return (1);
		}
		else if (check_for_err(cmd_current) == -1)
		{
			cmd_current->should_not_execute = 1;
			cmd_current->exit_code = cmd_current->data->last_exit_code;
			return (1);
		}
		token_current = token_current->next;
	}
	return (0);
}

void	check_errors(t_cmd *cmd_list, t_token **token_list)
{
	t_cmd	*cmd_current;
	t_token	*token_current;
	int		i;

	i = 0;
	cmd_current = cmd_list;
	while (cmd_current && token_list[i])
	{
		token_current = token_list[i];
		check_and_set_fd(cmd_current, token_current);
		if (!is_a_builtin(cmd_current->cmd))
			check_cmd_errors(cmd_current, token_current);
		i++;
		cmd_current = cmd_current->next;
	}
}
