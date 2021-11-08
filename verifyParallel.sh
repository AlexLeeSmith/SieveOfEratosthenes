# Usage: ./verifyParallel.sh <execName>

outFolder='Out'
binFolder='Bin'
outFile=$outFolder/'verify_parallel'

rm $outFile

./$binFolder/$1 2 3000000 1 > $outFile
diff -w $outFile $outFolder/primesThrough3Mil