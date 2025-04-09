/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/09 13:02:05 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	ft_readline(t_input *input)
{
	while (1)
	{
		input->readline_in = readline("$> ");
		if (input->readline_in == NULL)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		add_history(input->readline_in);
		ft_parse(input);
//		printf("%s\n", input->readline_in);
		free(input->readline_in);
	}
}

void	free_d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_parse(t_input *input)
{
	char	**full_cmd;
	int		i;

	i = 0;
	full_cmd = ft_split(input->readline_in, 32);

	input->cmd = full_cmd[0];
	if (ft_strchr(full_cmd[1], '-'))
		input->flags = full_cmd[++i];
	i++;
	input->args = full_cmd[i];
	ft_builtin(input);
	free_d_arr(full_cmd);
}

/*
 * Waiting for a good idea to parse!*/

void	ft_builtin(t_input *input)
{
	if (ft_strcmp(input->cmd, "cd") == 0)
		do_cd(input->args);
	if (ft_strcmp(input->cmd, "echo") == 0)
		do_echo(input);
	if (ft_strcmp(input->cmd, "env") == 0)
		do_env(input);
	if (ft_strcmp(input->cmd, "exit") == 0)
		do_exit();
	if (ft_strcmp(input->cmd, "export") == 0)
		do_export();
	if (ft_strcmp(input->cmd, "pwd") == 0)
		do_pwd();
	if (ft_strcmp(input->cmd, "unset") == 0)
		do_unset();
}
