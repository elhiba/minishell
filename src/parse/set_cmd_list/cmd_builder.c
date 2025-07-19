/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:55:28 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/19 16:25:19 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	set_cmd_name(t_cmd *cmd, t_token *token, t_data *data)
{
	t_env	*envp;
	char	**stock;

	envp = ft_collector(sizeof(t_env), ALLOC);
	envp->name = ft_strdup("PATH");
	envp->name_len = 4;
	get_env_value(data->env, envp);
	stock = ft_split(envp->value, ':');
	if (*token->arg && check_absolute_path(token->arg))
		cmd->cmd = get_full_path(stock, token->arg, &cmd->cmd_not_found);
	else
		cmd->cmd = token->arg;
	if (!*token->arg && (token->is_dquote || token->is_squote))
		cmd->cmd_not_found = 1;
	cmd->argv[0] = ft_strdup(token->arg);
	cmd->argv[1] = NULL;
	return (0);
}

void	add_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*curr;

	curr = *cmd;
	if (!*cmd)
		*cmd = new;
	else
	{
		curr = *cmd;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	init_stuff(t_token *head, t_cmd *node)
{
	node->cmd = NULL;
	node->argv = ft_collector(sizeof(char *) * (count_argv(head) + 1), ALLOC);
	node->argv[0] = NULL;
	node->heredcs = NULL;
	node->stdin_ = 0;
	node->stdout_ = 1;
	node->next = NULL;
}

void	do_while(t_token *current, t_cmd *node, t_data *data, int *flag)
{
	if (current->is_heredoc == HEREDOC)
		handle_heredoc(node, current, data);
	else if (*flag && is_valid_cmd_name(current))
	{
		*flag = 0;
		if (set_cmd_name(node, current, data) == -1)
			node->should_not_execute = 1;
	}
	else if (!(current->is_env_var && !current->arg[0] && !current->is_dquote)
		&& !current->is_ambiguous
		&& !is_redir(current))
		add_to_argv(node, current);
}

void	cmd_builder(t_cmd **cmd_list, t_token *head, t_data *data)
{
	t_token	*current;
	t_cmd	*node;
	int		flag;

	flag = 1;
	node = ft_collector(sizeof(t_cmd), ALLOC);
	init_stuff(head, node);
	node->data = data;
	current = head;
	while (current)
	{
		do_while(current, node, data, &flag);
		current = current->next;
	}
	if (node->cmd && !ft_strcmp("ls", get_cmd_name(node->argv[0])))
		node->argv = realloc_argv(node->argv);
	add_cmd(cmd_list, node);
} 