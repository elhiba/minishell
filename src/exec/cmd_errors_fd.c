/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:12:30 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/21 11:13:41 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_and_set_fd(t_cmd *cmd_current, t_token *token_current)
{
	while (token_current)
	{
		if (is_redir(token_current))
		{
			if (!token_current->is_heredoc
				&& check_redir_err(token_current, cmd_current->data) == -1)
			{
				cmd_current->should_not_execute = 1;
				cmd_current->exit_code = cmd_current->data->last_exit_code;
				return (1);
			}
			else if (!token_current->is_heredoc
				&& set_fd(cmd_current, token_current, cmd_current->data) == -1)
			{
				cmd_current->should_not_execute = 1;
				cmd_current->exit_code = cmd_current->data->last_exit_code;
				return (1);
			}
			else if (token_current->is_heredoc)
				cmd_current->use_last_heredoc = 1;
		}
		token_current = token_current->next;
	}
	return (0);
}
