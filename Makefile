# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjesse <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 17:09:44 by bjesse            #+#    #+#              #
#    Updated: 2019/06/18 21:22:39 by bjesse           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SOURCE = fillit.c grt_tet.c list_works.c service_functions.c  main.c

OBJ = $(patsubst %.c,%.o,$(SOURCE))

LIB = -L libft -lft

all: $(NAME)

%.o: %.c
	gcc -Wall -Wextra -Werror -c -o $@ $<

$(NAME): $(OBJ)
	make -C ./libft
	gcc -o $(NAME) $(SOURCE:.c=.o) $(LIB)

clean:
	/bin/rm -f $(SOURCE:.c=.o)
	make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./libft fclean

re: fclean all
