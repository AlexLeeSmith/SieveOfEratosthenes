#! /bin/bash
# Runs each OpenMP sieve method with various inputs to compare their runtimes.
# 
# Alex Smith (SmithAlexLee30@gmail.com)
# 8/20/22

# Load the config file.
source .config

# Compile omp driver.
make -s $ompDriver

# Delete the old compare file if it exists.
rm -f $outOmpCompare

# Output start prompt.
echo -n "Comparing OpenMP..."

# Run the driver for each max, # of threads, and OpenMP sieve method.
for max in 100000000 1000000000 # 1e8, 1e9
do
    for nThreads in 1 2 5
    do
        for ompMethod in 'omp' 'romp' 'romptasks'
        do
            $ompDriver $nThreads $max $ompMethod 0 >> $outOmpCompare
        done
        echo '~~~~~~~~~~~~~~~' >> $outOmpCompare
    done
    echo '===============' >> $outOmpCompare
done

# Output the location of the comparison file.
echo -e "\rOpenMP results saved to: $outOmpCompare"