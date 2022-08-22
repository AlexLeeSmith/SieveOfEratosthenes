# 
# 
# Alex Smith (SmithAlexLee30@gmail.com)
# 8/20/22

BIN='Bin'
OUT='Out'
outFile=$OUT/'compare_omp.txt'

make ompDriver 1>'/dev/null'
make cleanCompareOMP 1>'/dev/null'

# N = 1e8, 1e9
for N in 100000000 1000000000
do
    for nThreads in 1 2 5
    do
        for serialMethod in 'omp' 'romp' 'romptasks'
        do
            "./$BIN/omp_driver" $nThreads $N $serialMethod 0 >> $outFile
        done
        echo '~~~~~~~~~~~~~~~' >> $outFile
    done
    echo '===============' >> $outFile
done

echo "Results saved to: $outFile"

make cleanOmpDriver 1>'/dev/null'