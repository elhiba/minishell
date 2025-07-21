/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:12:33 by slasfar           #+#    #+#             */
/*   Updated: 2025/07/21 11:13:46 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_a_directory(char *cmd)
{
	struct stat	statbuf;

	ft_bzero(&statbuf, sizeof(statbuf));
	if (!stat(cmd, &statbuf) && S_ISDIR(statbuf.st_mode))
		return (1);
	return (0);
}

int	error_execution(char *arg, char *erroname, t_err flag)
{
	char	*buff;

	buff = 0;
	if (flag == IS_DIR)
		buff = ft_strjoin3(PRG_NAME, arg, ": Is a directory\n");
	else if (flag == PERM_DENY)
		buff = ft_strjoin3(PRG_NAME, arg, ": Permission denied\n");
	else if (flag == NOR_FILE_DIREC)
		buff = ft_strjoin3(PRG_NAME, arg, ": No such file or directory\n");
	else if (flag == IS_SUS)
		buff = ft_strjoin3(PRG_NAME, arg, ": Is SuS\n");
	else
		buff = ft_strjoin3(PRG_NAME, arg,
				ft_strjoin(": ", ft_strjoin(erroname, "\n")));
	return (write(2, buff, ft_strlen(buff)));
}

int	check_for_err(t_cmd *cmd)
{
	if (is_a_directory(cmd->cmd))
		return (cmd->data->last_exit_code = 126,
			error_execution(cmd->argv[0], NULL, IS_DIR), -1);
	else if (access(cmd->cmd, F_OK) == 0)
	{
		if (access(cmd->cmd, X_OK) != 0)
			return (cmd->data->last_exit_code = 126,
				error_execution(cmd->argv[0], NULL, PERM_DENY), -1);
	}
	return (0);
}
