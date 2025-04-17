/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:59:49 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/17 19:49:58 by sel-maaq         ###   ########.fr       */
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
			exit(EXIT_SUCCESS);
		}
		add_history(data.readline_in);
		ft_parse(&data);
	}
	return (0);
}
