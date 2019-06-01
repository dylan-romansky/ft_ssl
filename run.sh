rm test test2
make reclean
./ft_ssl des-cbc -a -k deadbeef -v deadbeef -i in -o test
cat test
echo "\n"
./ft_ssl des-cbc -d -a -k deadbeef -v deadbeef -i test -o test2
cat test2
