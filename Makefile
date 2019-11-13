# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromansk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 21:18:25 by dromansk          #+#    #+#              #
#    Updated: 2019/11/13 00:38:19 by dromansk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

SRCS = ./src/ssl/*.c ./src/md5/*.c ./src/sha256/*.c ./src/sha224/*.c \
	   ./src/sha512/*.c ./src/sha384/*.c ./src/base64/*.c ./src/des/*.c

I = -I ./includes -I ./libft/includes

O = *.o

L = -L ./libft -lft

all: $(NAME)

$(NAME):
	make -C ./libft reclean
	gcc -Wall -Werror -Wextra $(I) -c $(SRCS)
	gcc -Wall -Werror -Wextra $(I) -o $(NAME) $(O) $(L)

clean:
	make -C ./libft clean
	rm -rf $(O)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME)

re: fclean all

reclean: re
	make clean

lre: fclean
	make -C ./libft lreclean
	gcc -Wall -Werror -Wextra -c $(I) $(SRCS) -fsanitize=address
	gcc -Wall -Werror -Wextra -o $(NAME) $(O) $(I) $(L) -fsanitize=address

lreclean: lre
	make clean

vre: fclean
	make -C ./libft vreclean
	gcc -Wall -Werror -Wextra -g -c $(I) $(SRCS)
	gcc -Wall -Werror -Wextra -g -o $(NAME) $(O) $(I) $(L)

vreclean: vre
	make clean

test: clean
	gcc -Wall -Werror -Wextra -c $(I) $(SRCS)
	gcc -Wall -Werror -Wextra -o $(NAME) $(O) $(I) $(L)
	make clean
	echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar"

comptest: fclean all
	make -c libft reclean
	make test

recomp: clean
	rm -rf $(NAME)
	make all
	make clean

rm: fclean
	rm -rf $(NAME).dSYM
