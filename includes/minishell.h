/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-maaq <sel-maaq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:16:17 by moel-hib          #+#    #+#             */
/*   Updated: 2025/04/30 22:33:07 by moel-hib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_token
{
	char			*arg;

	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_data
{
	char	*readline_in;
	char	**env;

	int		is_dquote;
	int		is_squote;

	t_token	*token_list;
	int		last_exit_code;
}	t_data;

/* Signal func */
void	handle_signals(void);
void	sigint_handler(int sig);

/* Parse */
void	ft_parse(t_data *data);
void	dollar_expand(t_data *data, t_token *token);
void	quotes_handler(t_data *data);
char	*ft_strjoin3(const char *str1, const char *middle, const char *str2);

/* error handler */
void	error_handler(char *error_name, t_data *data);

/* built in functions */
int		ft_builtin(t_data *data);
int		do_cd(t_data *data);
int		do_echo(t_token *token_list);
int		do_env(t_data *data);
int		do_exit(t_data *data);
int		do_export(t_data *data);
int		do_pwd(t_data *data);
int		do_unset(t_data *data);

/* env functions */
char	**copy_env(char **env);
void	sort_env(char **env);
void	ft_setenv(char ***env, char *key, char *val);
char	*ft_getenv(char *key, t_data *data);

/* Excecution! */
void	ft_execution(t_data *data);

/* clean-up functions */
void	free_d_arr(char **arr);
void	free_token_list(t_token **head);

/* New spliter function:
 * it can remove any other tabs stuff and replaced by space
 */
char	**ft_spliter(t_data *data);

/* Linked list stuff*/
void	add_token_node(t_token **head, char *arg);

#endif
