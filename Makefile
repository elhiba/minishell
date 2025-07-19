# Binary file
NAME = minishell

# Compilation steps!
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

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
		$(addprefix $(BUITIN), ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c) \
		$(addprefix $(EXEC), exec.c cmd_errors.c) \
		$(addprefix $(UTILS), signals.c error.c utils.c linked_list.c utils_env.c special_split.c) \
		$(addprefix $(PARSE), readline.c quotes_handling.c join_token.c split_expanded.c \
		$(addprefix prompt/, prompt_builder.c git_checker0.c git_checker1.c git_checker2.c) \
		$(addprefix dollar_expand/, dollar_expander.c expand.c expand_modifier.c) \
		$(addprefix syntax/, op_checkers.c syntax_checker.c) \
		$(addprefix set_cmd_list/, heredoc_utils.c cmd_path_utils.c argv_utils.c validation_utils.c cmd_builder.c exec_setup.c) \
		$(addprefix heredoc/, heredoc_expand.c heredoc.c) \
		$(addprefix spliter/, spliter.c spliter_utils0.c spliter_utils1.c spliter_utils2.c spliter_utils3.c) ) \
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
