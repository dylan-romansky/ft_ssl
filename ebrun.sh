rm test test2
make reclean
./ft_ssl des-ecb -a -k deadbeef -v deadbeef -i in -o test
cat test
echo "\n"
./ft_ssl des-ecb -d -a -k deadbeef -v deadbeef -i test -o test2
cat test2
