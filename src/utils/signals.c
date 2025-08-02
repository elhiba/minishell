/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:13:33 by moel-hib          #+#    #+#             */
/*   Updated: 2025/08/02 11:22:20 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigint(int sig)
{
	g_received_signal = SIGINT;
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handle_sigint;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		error_handler("sigaction", NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signal_handlers(int mode)
{
	if (mode == INTER)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == DEFAULT)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	set_to_default(void)
{
	setup_signal_handlers(DEFAULT);
}
