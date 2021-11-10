rm -f Bin/romp_sieve_test Out/romp_test_output
gcc -g -Wall -o Bin/romp_sieve_test romp_sieve_test.c -fopenmp -lm

outFolder='Out'
binFolder='Bin'
outFile=$outFolder/'romp_test_output'

for serial_limit in 0 1000 10000 100000 1000000 10000000
do
    ./$binFolder/romp_sieve_test 2 10000000 $serial_limit >> $outFile
done