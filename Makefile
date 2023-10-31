# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 12:53:44 by pnamnil           #+#    #+#              #
#    Updated: 2023/10/31 12:53:45 by pnamnil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS = pipex_bonus

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

MPATH = mandatory
MSRC = $(addprefix src/, pipex.c px_child_process.c px_utils.c \
		px_free.c px_split.c px_parse_cmd.c)
MOBJ = $(MSRC:%.c=%.o)

BPATH = bonus
BSRC = $(addprefix src/, pipex_bonus.c px_child_process_bonus.c\
		px_manage_pipe_bonus.c px_here_doc_bonus.c px_utils.c px_free_bonus.c\
		px_parse_cmd.c px_split.c)
BOBJ = $(BSRC:%.c=%.o)

all: $(NAME)

$(NAME): $(MOBJ)
	@make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(MOBJ) $(LIBFT_PATH)/$(LIBFT)  -o $(NAME)
	@echo "${GREEN}Pipex is compiled${NC}"

bonus: $(BONUS)

$(BONUS): $(BOBJ)
	@$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(BOBJ) $(LIBFT_PATH)/$(LIBFT)  -o $(BONUS)
	@cp $(BONUS) $(NAME)
	@echo "${GREEN}Pipex bonus is compiled${NC}"

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@rm -f src/*.o
	@echo "${GREEN}Remove object file${NC}"

fclean:
	@rm -f src/*.o
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@rm -f $(NAME) $(BONUS)
	@echo "${GREEN}Pipex project is cleaned${NC}"

re: fclean all

.PHONY: all clean fclean re bonus
