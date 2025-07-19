/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:16:17 by moel-hib          #+#    #+#             */
/*   Updated: 2025/07/19 12:14:04 by moel-hib         ###   ########.fr       */
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
# include <errno.h>
# include <dirent.h>

extern volatile sig_atomic_t	g_received_signal;

typedef struct s_data			t_data;

typedef enum e_signal_flag
{
	INTER,
	DEFAULT,
	SIGDOC
}	t_signal_flag;

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
	int				is_dollar;
	int				is_squote;
	int				is_dquote;
	int				is_infile;
	int				is_append;
	int				is_outfile;
	int				is_heredoc;
	int				is_env_var;
	int				is_ambiguous;
	int				not_expandable;
	int				is_not_splittable;
	int				is_space_next;

	char			*key;
	char			*value;
	char			*ambiguous_name;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_heredoc
{
	char				*heredoc_file;
	char				*heredoc_del;
	int					fd;
	int					expand;
	struct s_heredoc	*next;
}	t_heredoc;

/*
 * 	char			*cmd; // usr/bin/ls
	char			**argv; // {"ls", "-l"}
	t_heredoc		*heredcs; // linked list of heredocs
	int				cmd_not_found; // flag to handle cmd not found
	int				should_not_execute;
	t_data			*data;
	int				use_last_heredoc;
	t_heredoc		*last_heredoc;
	int				stdin_; // stdin rah bayna 
	int				stdout_;
	int				exit_code;
	struct s_cmd	*next; // rah bayna 
*/
typedef struct s_cmd
{
	char			*cmd;
	char			**argv;
	t_heredoc		*heredcs;
	int				cmd_not_found;
	int				should_not_execute;
	t_data			*data;
	int				use_last_heredoc;
	t_heredoc		*last_heredoc;
	int				stdin_;
	int				stdout_;
	int				exit_code;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char			*readline_in;
	char			**env;

	t_token			*token_list;
	int				last_exit_code;
	int				stdin_;
	int				stdout_;
}	t_data;

# define SYN_OP_ERROR "minishell: syntax error near unexpected token"
# define SYN_Q_ERROR "minishell: unexpected EOF while looking for matching"
# define MAX_PATH_SIZE 4096

/* debug*/
void	print_list(void **head);

/* Signal func */
void	handle_signals(void);
void	sigint_handler(int sig);

/* Syntax checker */
int		syntax_checker(t_data *data);
int		check_hereappend(char *str, int *i);
int		check_redirect(char *str, int *i);
int		check_pipe(char *str, int *i);

/* Parse */
void	ft_parse(t_data *data);
char	*dollar_handler(char *str, int *i);
char	*quotes_handler(char *str, int *i, int *flag);
void	ft_spliter(t_token **token, char *str, t_data *data);
char	*ft_strjoin3(const char *str1, const char *middle, const char *str2);
void	expand_variable(t_token *current, t_data *data,
			char **envp, char **token);
void	join_tokens(t_token **tokens);
int		check_is_expandable(t_token *current);
void	split_expanded(t_token **token, t_data *data);
void	check_and_expand(t_token **head, t_data *data, char **envp);
int		operator_cleaner(char *arg);
int		there_is_space(char *s);
int		all_spaces(char *s);
bool	is_white_space(char c);
bool	is_alnum_(char c);
bool	is_alpha_(char c);
bool	is_digit_(char c);
void	expand_variable_heredoc(t_data *data, char **envp, char **token);
int		is_it_expandable(char *buffer);
void	get_env_value(char **envp, t_env *env);
void	extract_variable_name(char *token, t_env *env);
char	*ft_trim(char *str, int len);
char	*prompt_builder(t_data *data);
void	cp_flag(t_token *dest, t_token *src);
void	check_errors(t_cmd *cmd_list, t_token **token_list);
bool	is_redir(t_token *current);
void	set_to_default(void);
void	set_to_inter(void);
void	heredoc(t_cmd *cmd_list);
int		is_a_directory(char *cmd);
int		empty_env_var(t_token *current);
void	execute(t_cmd *cmd_list, t_data *data);
int		is_a_builtin(char *name);
void	expand_verifier(t_token *current, char **token, void **data);

t_cmd	*exec_setup(void	**stock, t_data *data);

/* error handler */
void	error_handler(char *error_name, t_data *data);

/* built in functions */
int		ft_builtin(t_cmd *data);
int		do_cd(t_cmd *data);
int		do_echo(t_cmd *data);
int		do_env(t_cmd *data);
int		do_exit(t_cmd *data);
int		do_export(t_cmd *data);
int		do_pwd(t_cmd *data);
int		do_unset(t_cmd *data);

/* env functions */
char	**copy_env(char **env);
void	sort_env(char **env);
void	ft_setenv(char ***env, char *key, char *val);
char	*ft_getenv(char *key, t_data *data);
void	get_env_value(char **envp, t_env *env);

/* Excecution! */
//void	ft_execution(t_data *data);
void	multiple_pipes(t_data *data, t_cmd *cmd_list);

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

/* Utils */
char	*ft_strtrim(char *str, int limit);
int		ft_arglen(char **args);
char	*sea_ret(char **env, char *arg);

/* prompt */
char	*check_git(char *dir_path);
char	*get_parent_dir(char *current_path);
char	*cp_buffer(char *buffer);
char	*dir_name(t_data *data);
int		validate_branch_ref(char *git_root, char *head);
char	*read_head(int *git_type);
char	*search_for_git(void);
char	*format_exit_code(int exit_code);
char	*get_status_arrow(int exit_code);
char	*build_git_part(void);
int		is_git_valid(void);

#endif
