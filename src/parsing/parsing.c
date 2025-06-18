/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:02:52 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/18 16:07:23 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parsing_analyser(t_data *data)
{
	void	**args;
//	t_token	*token_list;
//	int		i;

//	i = 0;
//	token_list = NULL;
	if (!syntax_checker(data))
	{
		args = ft_tokenizer(data);
	//if (args)
	//	print_list(args);
	//printf("\nEXEC LIST:\n\n");
	//if (list)
	//		pretty_print_cmd_list(list);
	//	dollar_expand(data, token_list);
	//	data->token_list = token_list;
	//	if (ft_builtin(data) == 0 && token_list)
	//		ft_executioakn(data);
	//	else
	//		free_token_list(&token_list);
	}
}
