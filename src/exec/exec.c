/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:34:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/13 21:53:45 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_merge(char *arg)
{
	char *cmd;

	cmd = ft_strjoin("/bin/", arg);
	return (cmd);
}

void	ft_execution(char *arg, char *env, t_input *input)
{
	(void)env;
	pid_t	pid_child;
	int		status;
	char	*cmd;
	char	**argv = NULL;
	char	**envi = input->env;

	argv = (char **)malloc(sizeof(char *) * 2);
	*argv = input->token.arg;
	*(argv + 1) = NULL;

	cmd = ft_merge(arg);
	//*argv = arg;
	pid_child = fork();
	status = 0;

	if (pid_child > 0)
		wait(&status);
	if (pid_child == 0)
	{
		if (execve(cmd, argv, envi) == -1)
			error_handler(arg);
	}
}
