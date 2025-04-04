/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:16:17 by moel-hib          #+#    #+#             */
/*   Updated: 2025/03/31 19:45:42 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* standard input / output */
#include <stdio.h>

/* For shit realine lib */
#include <readline/readline.h>

/* Malloc and free */
#include <stdlib.h>

/* Handling signals */
#include <signal.h>

/* Signal func */
void	signal_init(void);
void	signal_handler(int sig);

/* error handler */
void	error_handler(char *error_name);

#endif
