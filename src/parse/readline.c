/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/04/09 16:04:13 by sel-maaq         ###   ########.fr       */
=======
/*   Updated: 2025/04/10 12:07:25 by moel-hib         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

<<<<<<< Updated upstream
void	free_d_arr(char **arr)
=======
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
		free(input->readline_in);
	}
}

void	ft_parse(t_input *input)
>>>>>>> Stashed changes
{
	t_token	*token;
	t_token	*node;
	char	**args;

	token = NULL;
	args = ft_split(input->readline_in, ' ');
	if (!args)
		error_handler("Split Args");

	while (*args)
	{
		node = create_node(*args);
		add_list(&token, node);
		args++;
	}

<<<<<<< Updated upstream
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
=======
	ft_builtin(token);
	//free_d_arr(args);
>>>>>>> Stashed changes
}

void	ft_builtin(t_token *input)
{
	if (ft_strcmp(input->arg, "cd") == 0)
		do_cd(input->arg);
	if (ft_strcmp(input->arg, "echo") == 0)
		do_echo(input);
	if (ft_strcmp(input->arg, "env") == 0)
		do_env();
	if (ft_strcmp(input->arg, "exit") == 0)
		do_exit();
	if (ft_strcmp(input->arg, "export") == 0)
		do_export();
	if (ft_strcmp(input->arg, "pwd") == 0)
		do_pwd();
	if (ft_strcmp(input->arg, "unset") == 0)
		do_unset();
}
