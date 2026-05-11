NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I.

SRCS = src/main.c \
       src/parser.c \
       src/init_shared.c \
       src/init_people.c \
       src/cleanup.c \
       src/time_start.c \
       src/utils.c \
       src/forks_ops.c \
       src/actions.c \
       src/person_routine.c \
       src/monitor.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean re
