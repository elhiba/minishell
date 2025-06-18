/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hib <moel-hib@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:16:17 by moel-hib          #+#    #+#             */
/*   Updated: 2025/06/18 16:27:02 by moel-hib         ###   ########.fr       */
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

#define SYN_OP_ERROR "minishell: syntax error near unexpected token"
#define SYN_Q_ERROR "minishell: unexpected EOF while looking for matching"

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

typedef struct s_data
{
	char	*line_read;
	char	**env;

//	t_token	*token_list;
	int		exit_status;
}	t_data;

/* Parsing */
void	**ft_tokenizer(t_data *data);

/* Tools */
int		syntax_checker(t_data *data);
char	**pipe_split(char const *s);
void	check_quotes(char *str, int i, int *is_dquote, int *is_squote);

#endif
