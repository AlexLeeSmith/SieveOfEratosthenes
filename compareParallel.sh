# @author Alex Smith (alsmi14@ilstu.edu)
# @date 11/14/21

outFolder='Out'
binFolder='Bin'
outFile=$outFolder/'compare_parallel_output'

make cleanCompareParallel
make omp

# N = 1e8, 1e9
for N in 100000000 1000000000
do
    for nThreads in 1 2 5 10
    do
        ./$binFolder/omp_sieve $nThreads omp $N >> $outFile
        ./$binFolder/omp_sieve $nThreads romp $N >> $outFile
        echo ~~~~~~~~~~~~~~~ >> $outFile
    done
    echo =============== >> $outFile
done
