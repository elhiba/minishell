# Binary file
NAME = minishell

# Compilation steps!
CC = cc
CFLAGS = -g3 #-Wall -Wextra -Werror
# Lib include
CLIB = -lreadline

# Libft
LIBFT_PATH = includes/libft/
LIBFT = includes/libft/libft.a

# GCFT
GCFT = includes/gcft/gc_collector.c

# src path
SRC = src/

# FOLDERS
BUITIN = $(SRC)built_in/
EXEC = $(SRC)exec/
UTILS = $(SRC)utils/
PARSE = $(SRC)parse/

# C files
FILES = $(addprefix $(SRC), main.c) \
		$(addprefix $(BUITIN), ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_pwd.c ft_unset.c \
		$(addprefix export/, ft_export.c ft_export_tools.c) ) \
		$(addprefix $(EXEC), cmd_errors_file.c cmd_errors_redir.c cmd_errors_fd.c cmd_errors_cmd.c exec_utils.c \
		exec_status.c exec_multi.c exec_single.c exec_entry.c) \
		$(addprefix $(UTILS), signals.c error.c utils.c linked_list.c utils_env.c special_split.c) \
		$(addprefix $(PARSE), readline.c quotes_handling.c join_token.c \
		$(addprefix prompt/, prompt_builder.c git_checker0.c git_checker1.c git_checker2.c) \
		$(addprefix dollar_expand/, dollar_expander.c expand.c expand_modifier.c) \
		$(addprefix syntax/, op_checkers.c syntax_checker.c) \
		$(addprefix set_cmd_list/, heredoc_utils.c cmd_path_utils.c argv_utils.c validation_utils.c cmd_builder.c exec_setup.c) \
		$(addprefix heredoc/, heredoc.c heredoc_expand.c heredoc_tools0.c heredoc_tools1.c) \
		$(addprefix spliter/, spliter.c spliter_utils0.c spliter_utils1.c spliter_utils2.c spliter_utils3.c) \
		$(addprefix split_expander/, split_expanded.c split_util.c) ) \
		$(GCFT)

OBJ = $(FILES:.c=.o)

# COLORS
GREEN = \e[1;32m
BLUE = \e[4;34m
RESET = \e[0m

# Rule to make $(NAME)
all: $(NAME)

# make features

val: fresh
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp -q ./minishell

run: fresh
	./$(NAME)

fresh: all clean clearscr

clearscr:
	clear

# ----------------------------------- #

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $^ $(CLIB) $(LIBFT) -o $@
	@echo "$(GREEN)Your$(RESET) 🗽 $(BLUE)$(NAME)$(RESET) 🗽 $(GREEN)is ready to run!$(RESET)"
	@echo "\e[1;31m THIS FILE SHOULD BE REVIEWED >> utils_env.c <<\e[1;0m"
	@echo "\e[1;31m->>>> U REMOVED -Wall -Wextra -Werror! <<<<-\e[1;0m"

%.o: %.c
	@$(CC) $(CFLAGS) -c $<  -o $@
	@echo "$(GREEN)Building:$(RESET) $(BLUE)$(notdir $<)$(RESET) ✅"

$(LIBFT):
	@make -s -C $(LIBFT_PATH)

clean:
	@echo "🧼 $(GREEN)Cleaning$(RESET) 🧼"
	@rm -f $(OBJ)
	@make -s -C $(LIBFT_PATH) clean
	@echo "✨ $(GREEN)All obj files removed!$(RESET) ✨"

fclean: clean
	@rm -f $(NAME)
	@make -s -C $(LIBFT_PATH) fclean
	@echo "✨ $(GREEN)Binary files and libs deleted successfully!$(RESET) ✨"

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
