# Usage: ./verifySerial.sh <execPath>

outFolder='Out'
outFileEven=$outFolder/'verify_even'
outFileOdd=$outFolder/'verify_odd'

make cleanVerify

./$1 3000000 1 > $outFileEven
./$1 2999999 1 > $outFileOdd
diff -w $outFileEven $outFolder/primesThrough3Mil
diff -w $outFileOdd $outFolder/primesThrough3Mil