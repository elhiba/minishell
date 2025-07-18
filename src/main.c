/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:59:49 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/18 14:44:09 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_received_signal = 0;

void	init_stuff_main(char **env, t_data *data, ...)
{
	data->env = copy_env(env);
	data->stdin_ = dup(STDIN_FILENO);
	data->stdout_ = dup(STDOUT_FILENO);
	set_to_inter();
}

void	mini_init(char **prompt_add, t_data *data)
{
	handle_signals();
	*prompt_add = prompt_builder(data);
	rl_outstream = stderr;
	(*data).readline_in = readline(*prompt_add);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*prompt;

	ft_bzero(&data, sizeof(data));
	init_stuff_main(env, &data, ac, av);
	while (1337)
	{
		mini_init(&prompt, &data);
		if (g_received_signal == SIGINT)
		{
			data.last_exit_code = 130;
			g_received_signal = 0;
		}
		if (data.readline_in == NULL)
		{
			write(2, "exit\n", 5);
			close(data.stdin_);
			close(data.stdout_);
			ft_collector(0, FREE);
			exit(data.last_exit_code);
		}
		if (*data.readline_in && data.readline_in)
			add_history(data.readline_in);
		ft_parse(&data);
	}
}
