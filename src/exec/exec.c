/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:34:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/13 12:03:36 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_merge(char *arg)
{
	char *cmd;

	cmd = ft_strjoin("/bin/", arg);
	return (cmd);
}

void	ft_execution(char *arg, char *env)
{
	(void)env;
	pid_t	father;
	int	*status;
	char	*cmd;
	char	*argv[] = {NULL};
	char	*envi[] = {"PATH=Djaja", "libft=alo", NULL};

	cmd = ft_merge(arg);
	//*argv = arg;
	father = fork();
	status = NULL;

	if (father > 0)
		wait(status);
	if (father == 0)
	{
		if (execve(cmd, argv, envi) == -1)
			error_handler(arg);
	}
}
