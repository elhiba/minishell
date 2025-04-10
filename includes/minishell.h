/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:16:17 by moel-hib          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2025/04/09 15:50:53 by sel-maaq         ###   ########.fr       */
=======
/*   Updated: 2025/04/10 12:07:14 by moel-hib         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_token
{
	char *arg;

	struct s_token *next;
	struct s_token *prev;
} t_token;

typedef struct s_input
{
	char	*readline_in;

	char	*args;
	char	**env;

	t_token token;
	//char	*cmd;
	//char	*flags;
}	t_input;


/* Signal func */
void	handle_signals(void);
void	sigint_handler(int sig);

/* Parse */
void	ft_parse(t_input *input);

/* error handler */
void	error_handler(char *error_name);

/* built in functions */
void	ft_builtin(t_token *input);
int		do_cd(char *path);
int		do_echo(t_token *input);
void	do_env(void);
int		do_exit(void);
int		do_export(void);
int		do_pwd(void);
int		do_unset(void);

/* cleaner functions */
void	free_d_arr(char **arr);

/* New split functions*/
char	**ft_splits(char *arg, char *delimits);

/* Linked list stuff*/
t_token	*create_node(char *arg);
void	add_list(t_token **head, t_token *node);

#endif
