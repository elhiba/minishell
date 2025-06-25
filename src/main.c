/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:59:49 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/25 17:45:24 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_received_signal = 0;

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char *prompt;

	(void) ac;
	(void) av;
	ft_bzero(&data, sizeof(data));
	data.env = copy_env(env);
	handle_signals();
	while (1)
	{
		prompt = prompt_builder();
		data.readline_in = readline(prompt);
		if (g_received_signal == SIGINT)
		{
			data.last_exit_code = 130;
			g_received_signal = 0;
		}
		if (data.readline_in == NULL)
		{
			printf("exit\n");
			ft_collector(0, EXIT);
		}
		add_history(data.readline_in);
		ft_parse(&data);
	}
	return (0);
}
	
