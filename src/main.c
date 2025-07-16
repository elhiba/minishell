/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:59:49 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/16 17:05:42 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_received_signal = 0;

void	init_stuff_main(char **env, t_data *data, ...)
{
	data->env = copy_env(env);
	data->STDIN = dup(STDIN_FILENO);
	data->STDOUT = dup(STDOUT_FILENO);
	set_to_inter();
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char *prompt;

	if (!isatty(STDIN_FILENO))
		return (1);
	else if (!isatty(STDOUT_FILENO))
		return (write(2, "its not mandatory to handle non-interactive mode\n", 50), 1);
	else if (!isatty(STDERR_FILENO))
		return (write(2, "its not mandatory to handle non-interactive mode\n", 50), 1);
	ft_bzero(&data, sizeof(data));
	init_stuff_main(env, &data, ac, av);
	while (1337)
	{
		handle_signals();
		prompt = prompt_builder(&data);
		rl_outstream = stderr;
		data.readline_in = readline(prompt);
		if (g_received_signal == SIGINT)
		{
			data.last_exit_code = 130;
			g_received_signal = 0;
		}
		if (data.readline_in == NULL)
		{
			printf("exit\n");
			close(data.STDIN);
			close(data.STDOUT);
			ft_collector(0, EXIT);
		}
		if (*data.readline_in && data.readline_in)
			add_history(data.readline_in);
		ft_parse(&data);
	}
	return (0);
}
