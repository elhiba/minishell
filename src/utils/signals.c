/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:13:33 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/17 11:02:22 by slasfar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * I should search about interactive mode and non interactive mode! 
 * to make sure everystuff works fine if we for a minishell or any other non interactive file(script)
 * */

void	handle_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_flags = 0;
	sa.sa_handler = sigint_handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		error_handler("sigaction", NULL);
	signal(SIGQUIT, SIG_IGN);
}


void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_received_signal = SIGINT;
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

void handle_sigint(int sig)
{
	if(sig == SIGINT)
	{
		g_received_signal = SIGINT;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
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

void	set_to_inter(void)
{
	setup_signal_handlers(INTER);
}
