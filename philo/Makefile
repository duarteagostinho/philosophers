.SILENT:
NAME = philo
SRCS = utils/utils.c utils/utils2.c src/check.c src/init.c src/main.c src/mods.c src/actions.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra -g
INCLUDES = header.h

all: $(NAME)

$(NAME): $(OBJS)
	@echo "FILES COMPILED"
	@cc $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(INCLUDES)
	@cc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@echo "REMOVING OBJECT FILES"

fclean: clean
	@rm -rf $(NAME)
	@echo "REMOVING EXECUTABLE"

re: fclean all

.PHONY: all clean fclean re
