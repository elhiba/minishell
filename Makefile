# Binary file
NAME = minishell

# Compilation steps!
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Lib include
CLIB = -lreadline

# Libft
LIBFT_PATH = includes/libft/
LIBFT = includes/libft/libft.a

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
		$(addprefix $(EXEC), exec.c) \
		$(addprefix $(UTILS), signals.c error.c) \
		$(addprefix $(PARSE), readline.c)

OBJ = $(FILES:.c=.o)

# COLORS
GREEN = \e[1;32m
BLUE = \e[4;34m
RESET = \e[0m

# Rule to make $(NAME)
all: $(NAME)

run : fresh
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
