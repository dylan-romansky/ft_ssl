# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromansk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/22 14:53:52 by dromansk          #+#    #+#              #
#    Updated: 2019/03/31 00:41:50 by dromansk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ./src/printf/*.c ./src/printf/conversion/*.c \
./src/printf/parsing_and_handling/*.c ./src/printf/flags/*.c \
./src/printf/formatting_and_helpers/*.c ./src/libft/*.c \
./src/printf/colours/*.c

I = -I ./includes

O = *.o

L = -L ./ -lft

all: $(NAME)

$(NAME):
	gcc -Wall -Werror -Wextra $(I) $(SRCS) -c
	ar rcs $(NAME) $(O)
	ranlib $(NAME)

clean:
	rm -rf $(O)

fclean: clean
	rm -rf $(NAME)

re: fclean all

reclean: re
	make clean

sreclean:
	gcc -Wall -Werror -Wextra $(I) $(SRCS) -c -fsanitize=address -g
	ar rcs $(NAME) $(O)
	ranlib $(NAME)
	make clean

compile:
	gcc main.c $(I) $(L) -o ftest

scompile:
	gcc main.c $(I) $(L) -o ftest -fsanitize=address -g

test: sreclean
	make scompile
	./ftest

run: clean
	make compile
	./ftest

rm: fclean
	rm ftest main.c
