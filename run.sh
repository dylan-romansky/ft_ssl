rm test test2
make reclean
./ft_ssl des-ecb -k deadbeef -i in -o test
cat -e test
echo "\n"
./ft_ssl des-ecb -d -k deadbeef -i test -o test2
cat -e test2
