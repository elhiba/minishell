/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:13:33 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/04 22:49:01 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_init(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_flags = SA_RESTART;

	sa.sa_handler = signal_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		error_handler("sigaction");
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		error_handler("sigaction");
}

void	signal_handler(int sig)
{
	if (sig == SIGQUIT)
		return;

	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}
