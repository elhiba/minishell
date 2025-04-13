/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:16:17 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/13 21:50:47 by moel-hib         ###   ########.fr       */
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
# include <sys/wait.h>

typedef struct s_token
{
	char *arg;

	struct s_token *next;
	struct s_token *prev;
} t_token;

typedef struct s_input
{
	char	*readline_in;

	char	**env;
	char	**arg;

	t_token token;
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
int		ft_builtin(t_token *input);
int		do_cd(char *path);
int		do_echo(t_token *input);
int		do_env(void);
int		do_exit(void);
int		do_export(void);
int		do_pwd(void);
int		do_unset(void);

/* Excecution! */
void	ft_execution(char *arg, char *env, t_input *input);

/* cleaner functions */
void	free_d_arr(char **arr);

/* New spliter function:
 * it can remove any other tabs stuff and replaced by space
 */
char	**ft_spliter(char *args);

/* Linked list stuff*/
t_token	*create_node(char *arg);
void	add_list(t_token **head, t_token *node);

#endif
