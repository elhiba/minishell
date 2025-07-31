/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/31 19:41:34 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parse(t_data *data)
{
	void	**args;
	t_cmd	*list;

	list = NULL;
	if (!syntax_checker(data) && !all_spaces(data->readline_in))
	{
		args = ft_tokenizer(data);
		if (args)
			list = exec_setup(args, data);
		if (list)
			heredoc(list);
		if (list)
			check_errors(list, (t_token **)args);
		if (list)
			execute(list, data);
	}
	free(data->readline_in);
}

void	dup_to_redir(t_cmd *current)
{
	if (current->stdin_s != NULL)
	{
		current->stdin_ = open(current->stdin_s, O_RDONLY, 0644);
		dup2(current->stdin_, STDIN_FILENO);
		close(current->stdin_);
	}
	if (current->stdout_s != NULL)
	{
		current->stdout_ = open(current->stdout_s, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		dup2(current->stdout_, STDOUT_FILENO);
		close(current->stdout_);
	}
}

void	restore_std(t_data *data)
{
	dup2(data->stdin_, STDIN_FILENO);
	dup2(data->stdout_, STDOUT_FILENO);
}

int	cmd_verifier(t_cmd *data)
{
	t_cmd	*ptr;
	int		status;

	ptr = data;
	if (ft_strcmp(*ptr->argv, "cd") == 0)
		status = do_cd(data);
	else if (ft_strcmp(*ptr->argv, "echo") == 0)
		status = do_echo(data);
	else if (ft_strcmp(*ptr->argv, "env") == 0)
		status = do_env(data);
	else if (ft_strcmp(*ptr->argv, "exit") == 0)
		status = do_exit(data);
	else if (ft_strcmp(ptr->cmd, "export") == 0)
		status = do_export(data);
	else if (ft_strcmp(*ptr->argv, "pwd") == 0)
		status = do_pwd(data);
	else if (ft_strcmp(*ptr->argv, "unset") == 0)
		status = do_unset(data);
	else
		status = 0;
	return (status);
}

int	ft_builtin(t_cmd *data)
{
	int		status;

	status = 0;
	if (data->should_not_execute)
		return (1337);
	if ((!data || !data->argv))
		return (0);
	if (is_a_builtin(data->cmd))
	{
		dup_to_redir(data);
		status = cmd_verifier(data);
		restore_std(data->data);
	}
	return (status);
}
