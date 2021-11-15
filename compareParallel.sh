# @author Alex Smith (alsmi14@ilstu.edu)
# @date 11/14/21

outFolder='Out'
binFolder='Bin'
outFile=$outFolder/'compare_parallel_output'

make cleanCompareParallel
make omp
make romp

# N = 1e8, 1e9
for N in 100000000 1000000000
do
    for nThreads in 1 2 5 10
    do
        ./$binFolder/omp_sieve $nThreads $N >> $outFile
        ./$binFolder/romp_sieve $nThreads $N >> $outFile
        echo ~~~~~~~~~~~~~~~ >> $outFile
    done
    echo =============== >> $outFile
done
