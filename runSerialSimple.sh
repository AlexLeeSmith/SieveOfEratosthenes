make cleanSerialSimple
make serialSimple

outFolder='Out'
binFolder='Bin'
outFile=$outFolder/'serial_simple_output'

./$binFolder/serial_sieve_simple 10000 >> $outFile
./$binFolder/serial_sieve_simple 100000 >> $outFile
./$binFolder/serial_sieve_simple 1000000 >> $outFile
./$binFolder/serial_sieve_simple 10000000 >> $outFile