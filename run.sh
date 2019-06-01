rm test test2
make reclean
./ft_ssl des-cbc -k deadbeef -v deadbeef -i in -o test
cat test
echo "\n"
./ft_ssl des-cbc -d -k deadbeef -v deadbeef -i test -o test2
cat test2
