# Runs each OpenMP sieve method with various inputs to compare their runtimes.
# 
# Alex Smith (SmithAlexLee30@gmail.com)
# 8/20/22

# Directories
BIN='Bin'
OUT='Out'
outFile=$OUT/'compare_omp.txt'
driver="$BIN/omp_prime_driver"

# Compile omp driver.
make -s $driver

# Delete the old compare file if it exists.
make -s clean_compare_omp

# Run the driver for each max, # of threads, and OpenMP sieve method.
for max in 100000000 1000000000 # 1e8, 1e9
do
    for nThreads in 1 2 5
    do
        for ompMethod in 'omp' 'romp' 'romptasks'
        do
            "./$driver" $nThreads $max $ompMethod 0 >> $outFile
        done
        echo '~~~~~~~~~~~~~~~' >> $outFile
    done
    echo '===============' >> $outFile
done

# Output the location of the comparison file.
echo "Results saved to: $outFile"