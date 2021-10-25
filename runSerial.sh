make cleanSerial
make serial

outFolder='Out'
binFolder='Bin'
outFile=$outFolder/'serial_output'

./$binFolder/serial_sieve 10000 0 >> $outFile
./$binFolder/serial_sieve 100000 0 >> $outFile
./$binFolder/serial_sieve 1000000 0 >> $outFile
./$binFolder/serial_sieve 10000000 0 >> $outFile