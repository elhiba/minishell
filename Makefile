# Binary file
NAME = minishell

# Compilation steps!
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a

# Lib include
CLIB = -lreadline

# src path
SRC = src/

UTILS = $(SRC)utils/

# C files
FILES = $(addprefix $(SRC), main.c) \
		$(addprefix $(UTILS), signals.c error.c)

OBJ   = $(FILES:.c=.o)

# Rule to make $(NAME)
all: $(NAME)

run : fresh
	./$(NAME)

fresh: all clean clearscr

clearscr:
	clear

# ----------------------------------- #

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ $(CLIB) $(LIBFT) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $<  -o $@

$(LIBFT):
	make -C libft

clean:
	@rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
