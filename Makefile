# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/13 09:20:32 by mtaylor           #+#    #+#              #
#    Updated: 2019/05/13 09:20:33 by mtaylor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Wextra -Werror -g

LIBFT_PATH = libft/
LIB = -I $(LIBFT_PATH) $(addprefix $(LIBFT_PATH), libft.a) -lcurses

FILES = main.c \
		shell.c \
		prompt.c \
		builtins.c \
		builtins_env.c \
		execute.c \
		error.c \
		structs.c

SRC = $(addprefix ./src/, $(FILES))


all: $(NAME)

$(NAME):
	make -s -C $(LIBFT_PATH)
	gcc $(LIB) $(SRC) -o $(NAME)

debug:
	make -s -C $(LIBFT_PATH)
	gcc $(FLAGS) $(LIB) $(SRC) -o $(NAME)

fsan:
	make -s -C $(LIBFT_PATH)
	gcc $(FLAGS) -fsanitize=address $(LIB) $(SRC) -o $(NAME)

clean:
	make -s -C $(LIBFT_PATH) clean

fclean: clean
	make -s -C $(LIBFT_PATH) fclean
	rm -f $(NAME)
	rm -f -R $(addsuffix .dSYM, $(NAME))

re: fclean all