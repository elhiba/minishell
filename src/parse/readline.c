/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/13 11:59:48 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_parse(t_input *input)
{
	t_token	*token;
	t_token	*node;
	char	**args;
	int		i;

	i = 0;
	token = NULL;
	args = ft_spliter(input->readline_in);
	if (!args)
		error_handler("Split Args");

	while (args[i])
	{
		node = create_node(args[i]);
		add_list(&token, node);
		i++;
	}

	if (ft_builtin(token) == 0)
		;
	else 
		ft_execution(token->arg, NULL);

	if (args)
		free_d_arr(args);
}

int	ft_builtin(t_token *input)
{
	int	status;

	status = 1;
	if (ft_strcmp(input->arg, "cd") == 0)
		status = do_cd(input->next->arg);
	if (ft_strcmp(input->arg, "echo") == 0)
		status = do_echo(input);
	if (ft_strcmp(input->arg, "env") == 0)
		status = do_env();
	if (ft_strcmp(input->arg, "exit") == 0)
		status = do_exit();
	if (ft_strcmp(input->arg, "export") == 0)
		status = do_export();
	if (ft_strcmp(input->arg, "pwd") == 0)
		status = do_pwd();
	if (ft_strcmp(input->arg, "unset") == 0)
		status = do_unset();
	return (status);
}
