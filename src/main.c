/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:59:49 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/18 18:34:13 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*build_prompt(t_data *data)
{
	char	cwd[1000];
	char	*prompt;

	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, ft_getenv("PWD", data),1000);
	prompt = ft_collector(1000, ALLOC);
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
	
