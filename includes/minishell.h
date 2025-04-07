/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:16:17 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/07 11:17:38 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_input
{
	char	*cmd;
	char	*flags;
	char	*inputs;
} t_input;

typedef struct s_data
{
	char	*readline_in;

	t_input	input;
} t_data;

/* Signal func */
void	signal_init(void);
void	signal_handler(int sig);

/* Parse */
void	ft_readline(t_data *vars);

/* error handler */
void	error_handler(char *error_name);

#endif
