mv test test.c
gcc -I ../../includes -I ../../libft/includes des_keys.c ft_des.c encode.c test.c reverse_perm.c cbc.c ecb.c -L ../../libft -lft -fsanitize=address -g
mv test.c test
