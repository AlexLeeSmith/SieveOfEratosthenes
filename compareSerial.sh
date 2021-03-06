# @author Alex Smith (alsmi14@ilstu.edu)
# @date 11/14/21

outFolder='Out'
binFolder='Bin'
outFile=$outFolder/'compare_serial_output'

make cleanCompareSerial
make all

# N = 1e4, 1e6, 1e8
for N in 10000 1000000 100000000
do
    ./$binFolder/serial_sieve_simple $N >> $outFile
    ./$binFolder/serial_sieve_odds $N >> $outFile
    ./$binFolder/serial_sieve_1379 $N >> $outFile
    ./$binFolder/omp_sieve 1 omp $N >> $outFile
    ./$binFolder/omp_sieve 1 romp $N >> $outFile
    echo =============== >> $outFile
done
