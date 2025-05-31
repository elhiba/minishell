/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:16:17 by moel-hib          #+#    #+#             */
/*   Updated: 2025/05/31 16:31:49 by moel-hib         ###   ########.fr       */
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
# include <stdbool.h>

typedef enum s_type
{
	SPACES,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	INPUT_FILE,
	OUTPUT_FILE,
	HEREDOC,
	REDIRECTION
}	t_type;

typedef struct s_env
{
	char	*name;
	char	*value;
	long	name_len;
	long	value_len;
}	t_env;

typedef struct s_token
{
	char			*arg;

	int				is_squote;
	int				is_dquote;
	int				is_infile;
	int				is_outfile;
	int				is_heredoc;
	int				is_redirection;

	int				is_env_var;

	int				is_space_next;

	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_data
{
	char	*readline_in;
	char	**env;

	t_token	*token_list;
	int		last_exit_code;
}	t_data;

#define SYN_OP_ERROR "minishell: syntax error near unexpected token"
#define SYN_Q_ERROR "minishell: unexpected EOF while looking for matching"

/* debug*/
void	print_list(void **head);

/* Signal func */
void	handle_signals(void);
void	sigint_handler(int sig);

/* Parse */
void	ft_parse(t_data *data);
int		syntax_checker(t_data *data);
char	*dollar_handler(char *str, int *i);
char	*quotes_handler(char *str, int *i, int *flag);
void	ft_spliter(t_token **token, char *str, t_data *data);
char	*ft_strjoin3(const char *str1, const char *middle, const char *str2);
void	expand_variable(char **envp, char **token);
void	join_tokens(t_token **tokens);
int		check_is_expandable(char *buffer);
void	split_expanded(t_token **token, t_data *data);

/* error handler */
void	error_handler(char *error_name, t_data *data);

/* built in functions */
int		ft_builtin(t_data *data);
int		do_cd(t_data *data);
int		do_echo(t_data *data);
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
void	**ft_tokenizer(t_data *data);
char	**special_split(char const *s, char c);
void	check_quotes(char *str, int i, int *is_dquote, int *is_squote);

/* Linked list stuff*/
void	add_token_node(t_token **head, char *arg);

#endif
