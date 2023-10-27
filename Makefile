NAME = pipex

LIBFT = libft.a
LIBFT_PATH = libft

CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_PATH)/includes

NC="\\033[0m"
BOLD="\\033[1m"
ULINE="\\033[4m"
RED="\\033[31m"
GREEN="\\033[32m"
YELLOW="\\033[33m"
BLUE="\\033[34m"
MAGENTA="\\033[35m"

# MPATH = mandatory
MSRC = $(addprefix src/, pipex.c child_process.c px_utils.c px_parse_cmd.c\
		px_free.c px_split.c)

# BPATH = bonus
BSRC = $(addprefix src/, pipex_bonus.c child_process_bonus.c\
		manage_pipe_bonus.c here_doc_bonus.c px_utils.c px_free_bonus.c\
		px_parse_cmd.c px_split.c)

all: $(NAME)

pclean: 
	@rm -f $(NAME)

$(NAME): pclean
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(MSRC) $(LIBFT_PATH)/$(LIBFT)  -o $(NAME)
	@echo "${GREEN}Pipex is compiled${NC}"

bonus: pclean
	@$(MAKE) -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(BSRC) $(LIBFT_PATH)/$(LIBFT)  -o $(NAME)
	@echo "${GREEN}Pipex bonus is compiled${NC}"

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean:
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo "${GREEN}Pipex project is cleaned${NC}"

re: fclean all

.PHONY: all clean fclean re bonus
