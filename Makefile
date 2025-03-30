# Binary file
NAME = minishell

# Compilation steps!
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Lib include
CLIB = -lreadline

# We back to those variables later (ofc after we finish mandatory!)
MANDATORY = mandatory/
BONUS = bonus/

# ------------ MANDATORY ------------ #

# src path
MANDATORY_SRC = src/

# C files
MANDATORY_FILES = $(addprefix $(MANDATORY_SRC), main.c)
MANDATORY_OBJ = $(MANDATORY_FILES:.c=.o)

# Rule to make $(NAME)
$(NAME): $(MANDATORY_OBJ)
	$(CC) $(CFLAGS) $< $(CLIB) -o $@

# ----------------------------------- #

%.o: %.c
	$(CC) $(CFLAGS) -c $<  -o $@

all: $(NAME)

clean:
	@rm -f $(MANDATORY_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(MANDATORY_OBJ)
