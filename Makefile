NAME = philosophers
FLAGS = -Wall -Werror -Wextra -Iincludes -pthread
SRCS = *.c

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) $(SRCS) -o $(NAME)
	@echo --Making Philosophers--
clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all
