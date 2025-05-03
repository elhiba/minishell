/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:13:33 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/01 17:10:22 by sel-maaq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern volatile sig_atomic_t	g_received_signal;

void	handle_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = sigint_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		error_handler("sigaction", NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_received_signal = sig;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}
