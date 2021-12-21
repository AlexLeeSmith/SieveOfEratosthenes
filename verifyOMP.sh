# Usage: ./verifyParallel.sh [Executable Path] [Method]
# Methods: OMP, ROMP, ROMPTASKS
#
# @author Alex Smith (alsmi14@ilstu.edu)
# @date 11/14/21

if [ $# -eq 2 ]
then
    outFolder='Out'
    outFileEven=$outFolder/'verify_even'
    outFileOdd=$outFolder/'verify_odd'

    make cleanVerify

    ./$1 10 3000000 $2 1 > $outFileEven
    ./$1 10 2999999 $2 1 > $outFileOdd
    diff -w $outFileEven $outFolder/primesThrough3Mil
    diff -w $outFileOdd $outFolder/primesThrough3Mil
else
    printf "\nUsage: ./verifyParallel.sh [Executable Path] [Method]\n"
    printf "\tMethods: OMP, ROMP, ROMPTASKS\n\n"
fi