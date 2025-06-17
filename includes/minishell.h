/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slasfar <slasfar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:16:17 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/17 10:23:13 by slasfar          ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/stat.h>

typedef enum s_type
{
	SPACES,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	INPUT_FILE,
	OUTPUT_FILE,
	HEREDOC,
	APPEND
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

	int				is_word;
	int				is_squote;
	int				is_dquote;
	int				is_infile;
	int				is_append;
	int				is_outfile;
	int				is_heredoc;
	int				is_env_var;
	int				is_ambiguous;
	int				is_space_next;

	char			*key;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_heredoc
{
	char	*heredoc_file;
	char	*heredoc_del;
	int		fd;
	struct s_heredoc *next;
} t_heredoc;


typedef struct s_cmd
{
	char	*cmd; // usr/bin/ls
	char	**argv; // {"ls", "-l"}
	t_heredoc	*heredcs; // linked list of heredocs
	int		cmd_not_found; // flag to handle cmd not found
	int		STDIN; // stdin rah bayna 
	int		STDOUT; // ta hade bayna asahbe
	struct s_cmd *next;
}	t_cmd;


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
void	expand_variable(t_token*current, char **envp, char **token);
void	join_tokens(t_token **tokens);
int		check_is_expandable(char *buffer);
void	split_expanded(t_token **token, t_data *data);
void	check_and_expand(t_token **head, char **envp);
int		operator_cleaner(char *arg);
int	there_is_space(char *s);

t_cmd	*exec_setup(void	**stock, t_data *data);
void    pretty_print_cmd_list(t_cmd *cmd_list);

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
void	get_env_value(char **envp, t_env *env);

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
