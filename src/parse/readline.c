/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/10 17:02:42 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parse(t_input *input)
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

	ft_builtin(token);
	//free_d_arr(args);
}

void	ft_builtin(t_token *input)
{
	if (ft_strcmp(input->arg, "cd") == 0)
		do_cd(input->next->arg);
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
