/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:34:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/14 14:41:25 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

char	*ft_merge(char *arg)
{
	char *cmd;
	cmd = ft_strjoin("/bin/", arg);
	return (cmd);
}



void	ft_execution(char *arg, char *env, t_data *data)
{
	(void)env;
	pid_t	pid_child;
	int		status;
	char	*cmd;
	char	**argv = NULL;
	char	**envi = data->env;

	argv = (char **)malloc(sizeof(char *) * 3);
	*argv = data->token_list->arg;
	if (data->token_list->next)
		argv[1] = data->token_list->next->arg;
	*(argv + 2) = NULL;

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
	free_token_list(&data->token_list);
	wait(&status);
}
