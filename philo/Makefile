CC = gcc

CFLAGS = -Wall -Wextra -Werror

PTHREAD = -pthread

HEADER = philosophers.h

NAME = philo

RM = rm -f

SRCS = philosophers.c init_philos.c start_philos.c finish_philos.c utils.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(PTHREAD) $^ -o $@

%.o: %.c $(HEADER)
	$(CC) -g -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

all:	$(NAME)

.PHONY:	all clean fclean re