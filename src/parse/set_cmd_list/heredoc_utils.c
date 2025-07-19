/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:55:28 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/19 16:49:24 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*read_rand(void)
{
	char	*buffer;
	int		fd;
	int		i;

	i = 0;
	buffer = ft_collector(17, ALLOC);
	ft_bzero(buffer, 17);
	fd = open("/dev/random", O_RDONLY);
	read(fd, buffer, 16);
	close(fd);
	while (i < 16)
	{
		buffer[i] = buffer[i] % 26 + 'a';
		if (!ft_isalpha(buffer[i]))
			buffer[i] = (i % 10) + 48;
		i++;
	}
	return (ft_strjoin("_", buffer));
}

int	count_heredoc(t_token *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (head->is_heredoc)
			count++;
		head = head->next;
	}
	return (count);
}

void	add_heredoc(t_heredoc **head, t_heredoc *new)
{
	t_heredoc	*curr;

	curr = *head;
	if (!*head)
		*head = new;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}

void	handle_heredoc(t_cmd *cmd, t_token *token, t_data *data)
{
	char		*heredoc_name;
	t_heredoc	*heredoc_node;

	(void)data;
	heredoc_node = ft_collector(sizeof(t_heredoc), ALLOC);
	heredoc_node->heredoc_del = token->arg;
	heredoc_name = ft_strjoin("heredoc", read_rand());
	heredoc_name = ft_strjoin("/tmp/", heredoc_name);
	heredoc_node->heredoc_file = heredoc_name;
	heredoc_node->expand = 1;
	if (token->is_dquote || token->is_squote)
		heredoc_node->expand = 0;
	add_heredoc(&cmd->heredcs, heredoc_node);
}
