/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:44:40 by moel-hib          #+#    #+#             */
/*   Updated: 2025/08/02 11:05:26 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}

void	prevent_exec(t_cmd *cmd_list)
{
	t_cmd	*cmd;

	cmd = cmd_list;
	while (cmd)
	{
		cmd->should_not_execute = 1;
		cmd = cmd->next;
	}
}

int	prevent_flag(int sigint_was_here)
{
	static int	i;

	if (sigint_was_here == 2)
	{
		i = 2;
		return (i);
	}
	else if (sigint_was_here == 1337)
	{
		i = 0;
		return (i);
	}
	else
		return (i);
}

void	write_heredoc_warning(t_heredoc *heredoc)
{
	char	*tmp;

	tmp = ft_strjoin("minishell: warning: here-document\
delimited by end-of-file (wanted `", heredoc->heredoc_del);
	tmp = ft_strjoin(tmp, "')\n");
	write (2, tmp, ft_strlen(tmp));
}
