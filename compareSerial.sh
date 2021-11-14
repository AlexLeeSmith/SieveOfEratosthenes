outFolder='Out'
binFolder='Bin'
outFile=$outFolder/'compare_serial_output'

make cleanCompareSerial
make all

for N in 10000 1000000 100000000
do
    ./$binFolder/serial_sieve_simple $N >> $outFile
    ./$binFolder/serial_sieve_enhanced $N >> $outFile
    ./$binFolder/omp_sieve 1 $N >> $outFile
    ./$binFolder/romp_sieve 1 $N >> $outFile
    echo =============== >> $outFile
done
