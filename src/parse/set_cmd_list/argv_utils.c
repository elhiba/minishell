/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:55:28 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/19 15:51:04 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_argv(t_token *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (!is_redir(head))
			count++;
		head = head->next;
	}
	return (count);
}

void	add_to_argv(t_cmd *cmd, t_token *token)
{
	int	index;

	index = 0;
	while (cmd->argv[index])
		index++;
	cmd->argv[index++] = token->arg;
	cmd->argv[index] = NULL;
}

char	**realloc_argv(char **old_argv)
{
	char	**new_argv;
	int		i;

	i = 0;
	while (old_argv[i])
		i++;
	new_argv = ft_collector(sizeof(char *) * (i + 2), ALLOC);
	i = 0;
	while (old_argv[i])
	{
		new_argv[i] = old_argv[i];
		i++;
	}
	new_argv[i++] = ft_strdup("--color");
	new_argv[i] = NULL;
	return (new_argv);
} 