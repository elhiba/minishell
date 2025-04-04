SRCS =  ft_atoi.c		ft_memset.c			ft_strlcpy.c \
		ft_bzero.c		ft_putchar_fd.c		ft_strlen.c \
		ft_calloc.c		ft_putendl_fd.c		ft_strmapi.c \
		ft_isalnum.c	ft_putnbr_fd.c		ft_strncmp.c \
		ft_isalpha.c	ft_putstr_fd.c		ft_strnstr.c \
		ft_isascii.c	ft_split.c			ft_strrchr.c \
		ft_isdigit.c	ft_strchr.c			ft_strtrim.c \
		ft_isprint.c	ft_memchr.c			ft_strdup.c	\
		ft_itoa.c		ft_memcmp.c	       	ft_striteri.c \
		ft_memcpy.c		ft_strjoin.c		ft_toupper.c \
		ft_memmove.c	ft_strlcat.c		ft_substr.c		ft_tolower.c

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