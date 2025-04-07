/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/07 19:05:19 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Waiting for a good idea to parse!*/

void	ft_builtin (t_data *vars)
{
	if (ft_strcmp(vars->input.cmd, "cd") == 0)
		do_cd(vars->input.inputs);
	if (ft_strcmp(vars->input.cmd, "echo") == 0)
		do_echo(vars->input.flags, vars->input.inputs);
	if (ft_strcmp(vars->input.cmd, "env") == 0)
		do_env();
	if (ft_strcmp(vars->input.cmd, "exit") == 0)
		do_exit();
	if (ft_strcmp(vars->input.cmd, "export") == 0)
		do_export();
	if (ft_strcmp(vars->input.cmd, "pwd") == 0)
		do_pwd();
	if (ft_strcmp(vars->input.cmd, "unset") == 0)
		do_unset();
}

void	ft_parse(t_data *vars)
{
	char	**full_cmd;

	full_cmd = ft_split(vars->readline_in, 32);
	
	vars->input.cmd = full_cmd[0];
	vars->input.inputs = full_cmd[1];

	ft_builtin(vars);
}

void	ft_readline(t_data *vars)
{
	while (1)
	{
		vars->readline_in = readline("$> ");
		if (vars->readline_in == NULL)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		ft_parse(vars);
//		printf("%s\n", vars->readline_in);
		add_history(vars->readline_in);
		free(vars->readline_in);
	}
}
