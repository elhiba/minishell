/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:59:49 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/01 17:54:57 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*build_prompt(t_data *data)
{
	char	cwd[1000];
	char	*prompt;

	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, ft_getenv("PWD", data),1000);
	prompt = malloc(1000);
	if (!prompt)
		return (NULL);
	snprintf(prompt, 10000,
		"┌──(minishell)-[%s]\n└─❯ ", cwd);
	return (prompt);
}

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
		prompt = build_prompt(&data);
		data.readline_in = readline(prompt);
		if (g_received_signal == SIGINT)
		{
			data.last_exit_code = 130;
			g_received_signal = 0;
		}
		free(prompt);
		if (data.readline_in == NULL)
		{
			printf("exit\n");
			free_d_arr(data.env);
			exit(EXIT_SUCCESS);
		}
		add_history(data.readline_in);
		ft_parse(&data);
	}
	return (0);
}
	