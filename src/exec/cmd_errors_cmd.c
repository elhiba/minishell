/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:12:27 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/21 11:13:39 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_cmd_errors(t_cmd *cmd_current, t_token *token_current)
{
	while (cmd_current->cmd && token_current
		&& !cmd_current->should_not_execute)
	{
		if (cmd_current->cmd_not_found)
		{
			if (!cmd_current->cmd[0])
				write(2, ft_strjoin3("minishell: \'",
						cmd_current->cmd, "\': command not found!\n"),
					ft_strlen(cmd_current->cmd) + 34);
			else
				write(2, ft_strjoin(cmd_current->cmd, ": command not found!\n"),
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
