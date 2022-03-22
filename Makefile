NAME = philosophers
FLAGS = -Wall -Werror -Wextra -Iincludes -pthread
SRCS = *.c

all: $(NAME)

$(NAME):
	@gcc $(FLAGS) $(SRCS) -o $(NAME)
	@echo --Making Philosophers--
clean:
	rm -f $(NAME)

fclean:
	@rm -f $(NAME)
	@echo --Clean As A Whistle--

re: fclean all
