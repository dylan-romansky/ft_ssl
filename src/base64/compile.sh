mv test test.c
gcc -I ../../includes -I ../../libft/includes *.c -L ../../libft -lft
mv test.c test
