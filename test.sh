make reclean
rm test2
./ft_ssl des-ecb -d -k deadbeef -i test -o test2
cat -e test2
