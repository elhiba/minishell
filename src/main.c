/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:38:47 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/18 15:53:58 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_received_signal = 0;

int	main(int ac, char **av, char **env)
{
	t_data	data;
	//char *prompt;

	(void) ac;
	(void) av;
	ft_bzero(&data, sizeof(data));
	data.env = env; // copy_env(env);
	// handle_signals(); handle signals!
	while (1)
	{
		//prompt = build_prompt(&data);
		data.line_read = readline("-> " /* prompt */);
		if (g_received_signal == SIGINT)
		{
			data.exit_status = 130;
			g_received_signal = 0;
		}
		if (data.line_read == NULL)
		{
			printf("exit\n");
			ft_collector(0, EXIT);
		}
		if (data.line_read && *data.line_read)
			add_history(data.line_read);
		//ft_parse(&data);
	}
	return (0);
}
