NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

AR = ar
ARFLAGS = crs

SRC =	ft_isalnum.c ft_split.c \
		ft_strchr.c ft_strdup.c \
		ft_strjoin.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c \
		ft_strncmp.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(ARFLAGS) $@ $^
	@echo "\e[1;32mYour \e[1;34m$(NAME)\e[0m \e[1;32mhas been created successfully!\e[0m"

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
