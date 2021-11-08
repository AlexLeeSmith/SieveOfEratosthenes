# Usage: ./verifyParallel.sh <execPath>

outFolder='Out'
outFileEven=$outFolder/'verify_parallel_even'
outFileOdd=$outFolder/'verify_parallel_odd'

rm $outFileEven $outFileOdd

./$1 2 3000000 1 > $outFileEven
./$1 2 2999999 1 > $outFileOdd
diff -w $outFileEven $outFolder/primesThrough3Mil
diff -w $outFileOdd $outFolder/primesThrough3Mil