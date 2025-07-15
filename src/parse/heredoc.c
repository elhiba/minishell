/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:53:22 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/07 01:54:44 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void    prevent_exec(t_cmd *cmd_list)
{
    t_cmd   *cmd;

    cmd = cmd_list;
    while (cmd)
    {
        cmd->should_not_execute = 1;
        cmd = cmd->next;
    }
}


// we should handle SIGINT exit (leaks)
void	heredoc(t_cmd *cmd_list)
{
	t_cmd		*cmd;
	t_heredoc	*current;
	char		*buffer;
    t_data      *data;
    int         status;
	pid_t		pid;

	cmd = cmd_list;
    data = cmd->data;
	current = NULL;
	while (cmd)
	{
		current = cmd->heredcs;
		while (current)
		{
            signal(SIGINT, SIG_IGN);
			pid = fork();
			if (!pid)
			{
				set_to_default();
				while (1337)
				{
					buffer = readline("> ");
					if (!ft_strcmp(buffer, current->heredoc_del))
						break ;
					if (is_it_expandable(buffer) && current->expand)
						expand_variable_heredoc(cmd->data->env,&buffer);
					ft_putendl_fd(buffer, current->fd);
				}
				close(current->fd);
                ft_collector(0, FREE);
                exit(0);
			}
			waitpid(pid, &status, WUNTRACED);
            if (WIFEXITED(status))
			    data->last_exit_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
		    {
		    	data->last_exit_code = 128 + WTERMSIG(status);
		    	if (WTERMSIG(status) == SIGSEGV)
		    		printf("%d Segmentation fault (core dumped) HEREDOC\n", pid);
		    	else if (WTERMSIG(status) == SIGTERM)
		    		printf("%d terminated HEREDOC", pid);
		    	else if (WIFSTOPPED(status))
		    	{
		    		data->last_exit_code = 128 + WSTOPSIG(status);
		    	}
                prevent_exec(cmd_list);
		    	write(1, "\n", 1);
		    }
			close(current->fd);
			if (cmd->STDIN != 0)
				close(cmd->STDIN);
			cmd->STDIN = open(current->heredoc_file, O_RDONLY);
			current = current->next;
		}
		cmd = cmd->next;
	}
}
