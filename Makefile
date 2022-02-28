NAME = philosophers
FLAGS = -Wall -Werror -Wextra -Iincludes -pthread
SRCS = *.c

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all
