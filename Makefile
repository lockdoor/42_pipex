NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = $(addprefix src/, pipex.c)
OBJ = $(patsubst src/%.c, bin/%.o, $(SRC))

bin/%.o: src/%.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
	bash test.sh
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf bin

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re