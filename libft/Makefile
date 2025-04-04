
FT_PRINTF_DIR = ft_printf

SRCS = $(wildcard *.c) $(wildcard $(FT_PRINTF_DIR)/*.c)

BONUS_SRCS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c \
	ft_lstmap_bonus.c


NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar -rcs

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $@ $^

bonus: $(OBJS) $(BONUS_OBJS)
	$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
	rm -f $(BONUS_OBJS) $(OBJS)

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus re fclean clean