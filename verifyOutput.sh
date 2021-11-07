# Usage: ./verifyOutput.sh <execName>

outFolder='Out'
outFile=$outFolder/'verify_output'

./$1 2 3000000 1 > $outFile
diff -w $outFile $outFolder/primesThrough3Mil