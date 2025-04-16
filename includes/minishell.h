/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:16:17 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/15 16:31:26 by sel-maaq         ###   ########.fr       */
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

typedef struct s_data
{
	char	*readline_in;

	char	**env;

	t_token *token_list;
}	t_data;


/* Signal func */
void	handle_signals(void);
void	sigint_handler(int sig);

/* Parse */
void	ft_parse(t_data *data);

/* error handler */
void	error_handler(char *error_name);

/* built in functions */
int		ft_builtin(t_data *data);
int		do_cd(char *path);
int		do_echo(t_token *token_list);
int		do_env(t_data *data);
int		do_exit(t_data *data);
int		do_export(void);
int		do_pwd(void);
int		do_unset(void);

/* Excecution! */
void	ft_execution(t_data *data);

/* clean-up functions */
void	free_d_arr(char **arr);
void	free_token_list(t_token **head);

/* New spliter function:
 * it can remove any other tabs stuff and replaced by space
 */
char	**ft_spliter(char *args);

/* Linked list stuff*/
void	add_token_node(t_token **head, char *arg);

#endif
