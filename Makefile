NAME = philo
SRCS = utils/utils2.c utils/utils.c check.c init.c main.c mods.c actions.c
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Werror -Wextra -g
INCLUDES = header.h

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(FLAGS) $(OBJS) -o $(NAME)
	@echo "COMPILING FILES"

%.o: %.c $(INCLUDES)
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@echo "REMOVING FILES"

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
