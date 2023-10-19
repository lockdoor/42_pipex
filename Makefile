NAME = pipex

LIBFT = libft.a
LIBFT_PATH = libft

CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_PATH)/includes

MPATH = mandatory
MSRC = $(addprefix $(MPATH)/, pipex.c utils.c debug.c)
MOBJ = $(patsubst $(MPATH)/%.c, bin/%.o, $(MSRC))

bin/%.o: $(MPATH)/%.c
	@mkdir -p bin
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
	./mytest.sh

$(NAME): $(MOBJ)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(MOBJ) $(LIBFT_PATH)/$(LIBFT)  -o $(NAME)

clean:
	rm -rf bin

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re