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

int	is_builtin(t_token *token)
{
	if (!token || !token->arg)
		return (0);
	if (!ft_strcmp(token->arg, "cd") || !ft_strcmp(token->arg, "export")
		|| !ft_strcmp(token->arg, "env") || !ft_strcmp(token->arg, "exit")
		|| !ft_strcmp(token->arg, "echo") || !ft_strcmp(token->arg, "pwd")
		|| !ft_strcmp(token->arg, "unset"))
		return (1);
	else
		return (0);
}

void	do_builtin(t_data *data, t_token *list, int exit_or_not)
{
	if (!data || !list || !list->arg)
		return ;
	if (ft_strcmp(list->arg, "cd") == 0)
		do_cd(data, list);
	else if (ft_strcmp(list->arg, "echo") == 0)
		do_echo(data, list);
	else if (ft_strcmp(list->arg, "env") == 0)
		do_env(data);
	else if (ft_strcmp(list->arg, "exit") == 0)
		do_exit(data, list);
	else if (ft_strcmp(list->arg, "export") == 0)
		do_export(data, list);
	else if (ft_strcmp(list->arg, "pwd") == 0)
		do_pwd(data);
	else if (ft_strcmp(list->arg, "unset") == 0)
		do_unset(data, list);
	if (exit_or_not)
	{
		full_cleanup(data);
		exit(data->last_exit_code);
	}
}
