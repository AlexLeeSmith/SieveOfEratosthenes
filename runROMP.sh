make cleanROMP
make romp

outFolder='Out'
binFolder='Bin'
outFile=$outFolder/'romp_output'

for N in 10000000 100000000 1000000000
do
    for nThreads in 1 2 5 10
    do
        ./$binFolder/romp_sieve $nThreads $N >> $outFile
    done
    echo =============== >> $outFile
done
