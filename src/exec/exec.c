/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:34:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/30 16:20:08 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full_path);
}

char	*check_in_path(t_token *list, t_data *data)
{
	char	*cmd;
	char	*full_cmd;
	char	**dirs;
	int		i;

	cmd = list->arg;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	dirs = ft_split(ft_getenv("PATH", data), ':');
	if (!dirs)
		error_handler("path malloc error", NULL);
	i = 0;
	while (dirs[i])
	{
		full_cmd = join_path(dirs[i], cmd);
		if (access(full_cmd, X_OK) == 0)
		{
			list->arg = full_cmd;
			return (free(cmd), free_d_arr(dirs), full_cmd);
		}
		free(full_cmd);
		i++;
	}
	free_d_arr(dirs);
	return (cmd);
}

char	**build_argv(t_data *data, t_token *tokens)
{
	char	**argv;
	int		count;
	int		i;
	t_token	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		error_handler("Malloc failed", data);
	i = 0;
	while (tokens)
	{
		argv[i] = tokens->arg;
		tokens = tokens->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

void	execute_cmd(t_data *data)
{
	int		status;
	pid_t	pid_child;
	char	*cmd;
	char	**argv;

	status = 0;
	cmd = check_in_path(data->token_list, data);
	argv = build_argv(data, data->token_list);
	pid_child = fork();
	if (pid_child > 0)
		wait(&status);
	if (pid_child == 0)
	{
		if (execve(cmd, argv, data->env) == -1)
		{
			if (ft_strchr(cmd, '/'))
				printf("%s: No such file or directory\n", cmd);
			else
				printf("%s: command not found\n", cmd);
			free(argv);
			free_token_list(&data->token_list);
			free_d_arr(data->env);
			exit(127);
		}
		(free(argv), error_handler(cmd, data));
	}
	if (WIFEXITED(status))
		data->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->last_exit_code = 128 + WTERMSIG(status);
	free_token_list(&data->token_list);
	free(argv);
}
