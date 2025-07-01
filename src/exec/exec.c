/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:34:38 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/01 22:58:13 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_pid(pid_t **pid, pid_t new_pid, int *size)
{
	pid_t	*new_pid_list;
	int		i;

	i = 0;
	new_pid_list = ft_collector(sizeof(pid_t) * (*size + 1), ALLOC);
	while (i < *size)
	{
		new_pid_list[i] = (*pid)[i];
		i++;
	}
	new_pid_list[i] = new_pid;
	*size += 1;
	*pid = new_pid_list;
}

void	multiple_pipes(t_data *data, t_cmd *cmd_list, char **env)
{
	t_cmd *current = cmd_list;
	pid_t	*pid_list;
	int		len = 0;
	t_cmd *last;
	int	fd[2];
	pid_t pid;
	int status = 0;
	current = cmd_list;
	while (current)
	{
		pipe(fd);
		if (current->cmd && !current->should_not_execute && !current->cmd_not_found)
		{
			signal(SIGINT, SIG_IGN);
			pid = fork();
			if (pid == 0)
			{
				set_to_default();
				if (current->next && !current->cmd_not_found)
					dup2(fd[1], STDOUT_FILENO);
				if (current->STDIN != 0)
				{
					dup2(current->STDIN, STDIN_FILENO);
					close(current->STDIN);
				}
				if (current->STDOUT != 1)
				{
					dup2(current->STDOUT, STDOUT_FILENO);
					close(current->STDOUT);
				}
				close(fd[0]);
				close(fd[1]);
				execve(current->cmd, current->argv, env);
				printf("minishell: %s: %s\n", current->argv[0], strerror(errno));
				if (errno == ENOENT)
					exit(127);
				else
					exit (126);
			}
			add_pid(&pid_list, pid, &len);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		last = current;
		current = current->next;
	}
	if (last->cmd && !last->should_not_execute && !last->cmd_not_found)
	{
		waitpid(pid_list[len - 1], &status, WUNTRACED);
		if (WIFEXITED(status))
			data->last_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			data->last_exit_code = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGSEGV)
				printf("%d Segmentation fault (core dumped) %s\n", pid, last->argv[0]);
			else if (WTERMSIG(status) == SIGTERM)
				printf("%s terminated", last->argv[0]);
			else if (WIFSTOPPED(status))
			{
				data->last_exit_code = 128 + WSTOPSIG(status);
			}
		}
	}
	pid = 0;
	if (len > 1)
	{
		while (pid < len)
			waitpid(pid_list[pid++], &status, WUNTRACED);
	}
}
//char	*join_path(const char *dir, const char *cmd)
//{
//	char	*tmp;
//	char	*full_path;
//
//	tmp = ft_strjoin(dir, "/");
//	full_path = ft_strjoin(tmp, cmd);
//	free(tmp);
//	return (full_path);
//}
//
//char	*check_in_path(t_token *list, t_data *data)
//{
//	char	*cmd;
//	char	*full_cmd;
//	char	**dirs;
//	int		i;
//
//	cmd = list->arg;
//	if (access(cmd, X_OK) == 0)
//		return (cmd);
//	dirs = ft_split(ft_getenv("PATH", data), ':');
//	if (!dirs)
//		error_handler("path malloc error", NULL);
//	i = 0;
//	while (dirs[i])
//	{
//		full_cmd = join_path(dirs[i], cmd);
//		if (access(full_cmd, X_OK) == 0)
//		{
//			list->arg = full_cmd;
//			return (full_cmd);
//		}
//		i++;
//	}
//	return (cmd);
//}
//
//char	**build_argv(t_data *data, t_token *tokens)
//{
//	char	**argv;
//	int		count;
//	int		i;
//	t_token	*tmp;
//
//	count = 0;
//	tmp = tokens;
//	while (tmp)
//	{
//		count++;
//		tmp = tmp->next;
//	}
//	argv = malloc(sizeof(char *) * (count + 1));
//	if (!argv)
//		error_handler("Malloc failed", data);
//	i = 0;
//	while (tokens)
//	{
//		argv[i] = tokens->arg;
//		tokens = tokens->next;
//		i++;
//	}
//	argv[i] = NULL;
//	return (argv);
//}
//
//void	ft_execution(t_data *data)
//{
//	int		status;
//	pid_t	pid_child;
//	char	*cmd;
//	char	**argv;
//
//	status = 0;
//	cmd = check_in_path(data->token_list, data);
//	argv = build_argv(data, data->token_list);
//	pid_child = fork();
//	if (pid_child > 0)
//		wait(&status);
//	if (pid_child == 0)
//	{
//		if (execve(cmd, argv, data->env) == -1)
//		{
//			if (ft_strchr(cmd, '/'))
//				printf("%s: No such file or directory\n", cmd);
//			else
//				printf("%s: command not found\n", cmd);
//			exit(127);
//		}
//		(error_handler(cmd, data));
//	}
//	if (WIFEXITED(status))
//		data->last_exit_code = WEXITSTATUS(status);
//	else if (WIFSIGNALED(status))
//		data->last_exit_code = 128 + WTERMSIG(status);
//}
