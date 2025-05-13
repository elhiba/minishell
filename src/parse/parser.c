/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/02 23:05:01 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//  void	print_list(t_token *head)
//  {
//  	while (head)
//  	{
//  		printf("%s\n", head->arg);
//  		head = head->next;
//  	}
// 	printf("THIS IS JUST A DEBUG!\n\n\n\n");
//  }

void	ft_parse(t_data *data)
{
	t_token	*token_list;
	char	**args;
	int		i;

	i = 0;
	token_list = NULL;
	quotes_handler(data);
	args = ft_spliter(data);
	if (!args)
		error_handler("Split Args", NULL);
	while (args[i])
		add_token_node(&token_list, args[i++]);
	free(args);
	dollar_expand(data, token_list);
	data->token_list = token_list;
}

int	is_builtin(t_data *data)
{
	t_token	*tok_list;

	if (!data || !data->token_list || !data->token_list->arg)
		return (0);
	tok_list = data->token_list;
	if (!ft_strcmp(tok_list->arg, "cd") || !ft_strcmp(tok_list->arg, "export")
		|| !ft_strcmp(tok_list->arg, "env") || !ft_strcmp(tok_list->arg, "exit")
		|| !ft_strcmp(tok_list->arg, "echo") || !ft_strcmp(tok_list->arg, "pwd")
		|| !ft_strcmp(tok_list->arg, "unset"))
		return (1);
	else
		return (0);
}

void	do_builtin(t_data *data)
{
	t_token	*tok_list;

	if (!data || !data->token_list || !data->token_list->arg)
		return (0);
	tok_list = data->token_list;
	if (ft_strcmp(tok_list->arg, "cd") == 0)
		do_cd(data);
	else if (ft_strcmp(tok_list->arg, "echo") == 0)
		do_echo(data);
	else if (ft_strcmp(tok_list->arg, "env") == 0)
		do_env(data);
	else if (ft_strcmp(tok_list->arg, "exit") == 0)
		do_exit(data);
	else if (ft_strcmp(tok_list->arg, "export") == 0)
		do_export(data);
	else if (ft_strcmp(tok_list->arg, "pwd") == 0)
		do_pwd(data);
	else if (ft_strcmp(tok_list->arg, "unset") == 0)
		do_unset(data);
}

void	do_builtin_fork(t_data *data)
{
	t_token	*tok_list;

	if (!data || !data->token_list || !data->token_list->arg)
		return (0);
	tok_list = data->token_list;
	if (ft_strcmp(tok_list->arg, "cd") == 0)
		do_cd(data);
	else if (ft_strcmp(tok_list->arg, "echo") == 0)
		do_echo(data);
	else if (ft_strcmp(tok_list->arg, "env") == 0)
		do_env(data);
	else if (ft_strcmp(tok_list->arg, "exit") == 0)
		do_exit(data);
	else if (ft_strcmp(tok_list->arg, "export") == 0)
		do_export(data);
	else if (ft_strcmp(tok_list->arg, "pwd") == 0)
		do_pwd(data);
	else if (ft_strcmp(tok_list->arg, "unset") == 0)
		do_unset(data);
	exit(data->last_exit_code);
}

// int	do_builtin(t_data *data)
// {
// 	t_token	*tok_list;
// 	int		status;

// 	if (!data || !data->token_list || !data->token_list->arg)
// 		return (0);
// 	tok_list = data->token_list;
// 	if (ft_strcmp(tok_list->arg, "cd") == 0)
// 		status = do_cd(data);
// 	else if (ft_strcmp(tok_list->arg, "echo") == 0)
// 		status = do_echo(data);
// 	else if (ft_strcmp(tok_list->arg, "env") == 0)
// 		status = do_env(data);
// 	else if (ft_strcmp(tok_list->arg, "exit") == 0)
// 		status = do_exit(data);
// 	else if (ft_strcmp(tok_list->arg, "export") == 0)
// 		status = do_export(data);
// 	else if (ft_strcmp(tok_list->arg, "pwd") == 0)
// 		status = do_pwd(data);
// 	else if (ft_strcmp(tok_list->arg, "unset") == 0)
// 		status = do_unset(data);
// 	else
// 		status = 0;
// 	return (status);
// }
