rm test test2
make reclean
./ft_ssl base64 -i in -o test
cat -e test
echo "\n"
./ft_ssl base64 -i test -o test2
cat -e test2
