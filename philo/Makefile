CC = gcc

CFLAGS = -Wall -Wextra -Werror

PTHREAD = -pthread

HEADER = philosophers.h

NAME = philo

RM = rm -f

SRCS := $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(PTHREAD) $^ -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

all:	$(NAME)

.PHONY:	all clean fclean re