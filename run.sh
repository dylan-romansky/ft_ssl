rm test test2
make reclean
./ft_ssl base64 -e -i in -o test
cat -e test
echo "\n"
./ft_ssl base64 -d -i test -o test2
cat -e test2
