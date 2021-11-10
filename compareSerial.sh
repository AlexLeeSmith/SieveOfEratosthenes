make cleanCompareSerial
make compareSerial

outFolder='Out'
binFolder='Bin'
outFile=$outFolder/'compare_serial_output'

for N in 10000 1000000 100000000
do
    ./$binFolder/serial_sieve_simple $N >> $outFile
    ./$binFolder/serial_sieve_enhanced $N >> $outFile
    echo =============== >> $outFile
done