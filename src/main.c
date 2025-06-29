/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:59:49 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/29 13:32:53 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_received_signal = 0;

void	init_stuff_main(char **env, t_data *data, ...)
{
	data->env = copy_env(env);
	set_to_inter();
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char *prompt;

	ft_bzero(&data, sizeof(data));
	init_stuff_main(env, &data, ac, av);
	while (1337)
	{
		prompt = prompt_builder(&data);
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
		if (*data.readline_in && data.readline_in)
			add_history(data.readline_in);
		ft_parse(&data);
	}
	return (0);
}
