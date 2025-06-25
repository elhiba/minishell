/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:52:19 by slasfar           #+#    #+#             */
/*   Updated: 2025/06/25 14:28:18 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	is_a_directory(char *cmd)
{
	struct stat statbuf;

	ft_bzero(&statbuf, sizeof(statbuf));
	stat(cmd, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
		return (1);
	return (0);
}

int	check_for_err(t_cmd *cmd)
{
	//if (access(cmd->cmd, F_OK) != 0)
	//	return (printf("minishell: %s: No such file or directory\n", cmd->cmd), -1);
	if (is_a_directory(cmd->cmd))
		return (printf("minishell: %s: Is a directory\n", cmd->cmd), -1);
	else if (access(cmd->cmd, F_OK) == 0)
	{
		if (access(cmd->cmd, X_OK) != 0)
			return (printf("minishell: %s: Permission denied\n", cmd->cmd), -1);
	}
	return (0);
}

bool	is_redir(t_token *current)
{
	if (current->is_infile || current->is_outfile
		|| current->is_append)
		return (true);
	return (false);
}

int	check_redir_err(t_token *current)
{
	if (current->is_ambiguous)
		return (printf("minishell: %s: is sus\n", current->ambiguous_name), -1);
	if (is_a_directory(current->arg))
		return (printf("minishell: %s: is a directory\n", current->arg), -1);
	//if (current->is_infile && access(current->arg, F_OK) != 0)
	//	return (printf("minishell: %s: No such file or directory\n", current->arg), -1);
	return (0);
}

int	set_fd(t_cmd *cmd, t_token *token, t_data *data)
{
	if (token->is_outfile == OUTPUT_FILE)
	{
		if (cmd->STDOUT != 1)
			close(cmd->STDOUT);
		cmd->STDOUT = open(token->arg, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (cmd->STDOUT == -1)
			return (perror(token->arg), -1);
	}
	else if (token->is_append == APPEND)
	{
		if (cmd->STDOUT != 1)
			close(cmd->STDOUT);
		cmd->STDOUT = open(token->arg, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (cmd->STDOUT == -1)
			return (perror(token->arg), -1);
	}
	else if (token->is_infile == INPUT_FILE)
	{
		if (cmd->STDIN != 0)
			close(cmd->STDIN);
		cmd->STDIN = open(token->arg, O_RDONLY, 0644);
		if (cmd->STDIN == -1)
			return (perror(token->arg), -1);
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
		while (token_current)
		{
			if (is_redir(token_current))
			{
				if (check_redir_err(token_current) == -1)
				{
					cmd_current->should_not_execute = 1;
					break ;
				}
				else if (set_fd(cmd_current, token_current, cmd_current->data) == -1)
				{
					cmd_current->should_not_execute = 1;
					break ;
				}
			}
			token_current = token_current->next;
		}
		token_current = token_list[i];
		while (token_current && !cmd_current->should_not_execute)
		{
			if (cmd_current->cmd_not_found)
			{
				if (!cmd_current->cmd[0])
					printf("minishell: \'%s\': command not found!\n", cmd_current->cmd);
				else
					printf("%s: command not found!\n", cmd_current->cmd);
				break ;
			}
			else if (check_for_err(cmd_current) == -1)
			{
				cmd_current->should_not_execute = 1;
				break;
			}
			token_current = token_current->next;
		}
		i++;
	}
}
