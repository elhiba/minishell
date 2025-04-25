/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:53:24 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/25 18:03:34 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	print_list(t_token *head)
// {
// 	while (head)
// 	{
// 		printf("%s\n", head->arg);
// 		head = head->next;
// 	}
// }

void	char_remover(t_data *data, char	*str, int	character)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != character)
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	if (character == '\"')
		data->is_dquote = 0;
	if (character == '\'')
		data->is_squote = 0;
}



void	ft_parse(t_data *data)
{
	t_token	*token_list;
	char	**args;
	int		i;

	i = 0;
	token_list = NULL;
	quotes_handler(data);
	args = ft_spliter(data->readline_in);
	if (!args)
		error_handler("Split Args", NULL);
	while (args[i])
		add_token_node(&token_list, args[i++]);
	free(args);
	dollar_expand(token_list);
	data->token_list = token_list;
	if (ft_builtin(data) == 0 && token_list)
		ft_execution(data);
	else
		free_token_list(&token_list);
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
		status = do_echo(tok_list);
	else if (ft_strcmp(tok_list->arg, "env") == 0)
		status = do_env(data);
	else if (ft_strcmp(tok_list->arg, "exit") == 0)
		status = do_exit(data);
	else if (ft_strcmp(tok_list->arg, "export") == 0)
		status = do_export();
	else if (ft_strcmp(tok_list->arg, "pwd") == 0)
		status = do_pwd();
	else if (ft_strcmp(tok_list->arg, "unset") == 0)
		status = do_unset();
	else
		status = 0;
	return (status);
}
