/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:59:49 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/14 11:17:47 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void) ac;
	(void) av;
	ft_bzero(&data, sizeof(data));
	data.env = env;
	handle_signals();
	while (1)
	{
		data.readline_in = readline("$> ");
		if (data.readline_in == NULL)
		{
			printf("exit\n");
			free_token_list(&data.token_list);
			exit(EXIT_SUCCESS);
		}
		add_history(data.readline_in);
		ft_parse(&data);
//		execute_cmd(data);
	}
	return (0);
}
