# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromansk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 21:18:25 by dromansk          #+#    #+#              #
#    Updated: 2019/03/06 19:55:12 by dromansk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = md5_test

SRCS = ./src/*.c ./src/md5/*.c

I = -I ./includes -I ./libft/includes

O = *.o

L = -L ./libft -lft

all: $(NAME)

$(NAME):
	make -C ./libft reclean
	gcc -Wall -Werror -Wextra -c $(I) $(SRCS)
	gcc -Wall -Werror -Wextra -o $(NAME) $(O) $(I) $(L)

clean:
	make -C ./libft clean
	rm -rf $(O)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re: fclean all

reclean: re
	make clean

test: clean
	gcc -Wall -Werror -Wextra -c $(I) $(SRCS)
	gcc -Wall -Werror -Wextra -o $(NAME) $(O) $(I) $(L)
	make clean
	./$(NAME) butt
