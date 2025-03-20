NAME = philo
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Werror -Wextra -g
INCLUDES = header.h

all: $(NAME)

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(INCLUDES)
	cc $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

