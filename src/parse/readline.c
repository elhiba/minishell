/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/20 20:29:58 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_list(void **head)
{
	int		i;
	t_token	**ptr;

	i = 0;
	ptr = (t_token **)head;
	while (ptr[i])
	{
		printf("Args[%i]: ", i);
		while (ptr[i])
		{
			printf("%s ", ptr[i]->arg);
			ptr[i] = ptr[i]->next;
		}
		printf("\n");
		i++;
	}
}

void	ft_parse(t_data *data)
{
//	t_token	*token_list;
	void	**args;
//	int		i;

//	i = 0;
//	token_list = NULL;
	if (!syntax_checker(data))
	{
//		quotes_handler(data);
		args = ft_tokenizer(data);
		if (!args)
			error_handler("Split Args", NULL);
		print_list(args);
		free(args);
	//	dollar_expand(data, token_list);
	//	data->token_list = token_list;
	//	if (ft_builtin(data) == 0 && token_list)
	//		ft_execution(data);
	//	else
	//		free_token_list(&token_list);
	}
}

int	ft_builtin(t_data *data)
{
	t_token	*tok_list;
	int		status;

	if (!data || !data->token_list || !data->token_list->arg)
		return (0);
	tok_list = data->token_list;
	if (ft_strcmp(tok_list->arg, "cd") == 0)
		status = do_cd(data);
	else if (ft_strcmp(tok_list->arg, "echo") == 0)
		status = do_echo(data);
	else if (ft_strcmp(tok_list->arg, "env") == 0)
		status = do_env(data);
	else if (ft_strcmp(tok_list->arg, "exit") == 0)
		status = do_exit(data);
	else if (ft_strcmp(tok_list->arg, "export") == 0)
		status = do_export(data);
	else if (ft_strcmp(tok_list->arg, "pwd") == 0)
		status = do_pwd(data);
	else if (ft_strcmp(tok_list->arg, "unset") == 0)
		status = do_unset(data);
	else
		status = 0;
	return (status);
}
