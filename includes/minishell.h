/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:16:17 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/09 14:22:19 by sel-maaq         ###   ########.fr       */
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
	char	*readline_in;
	char	*cmd;
	char	*flags;
	char	*args;
	char	**env;
}	t_input;


/* Signal func */
void	handle_signals(void);
void	sigint_handler(int sig);

/* Parse */
void	ft_readline(t_input *input);
void	ft_parse(t_input *input);

/* error handler */
void	error_handler(char *error_name);

/* built in functions */
void	ft_builtin(t_input *input);
int		do_cd(char *path);
int		do_echo(t_input *input);
void	do_env(t_input *input);
int		do_exit(void);
int		do_export(void);
int		do_pwd(void);
int		do_unset(void);

/* cleaner functions */
void	free_d_arr(char **arr);

#endif
