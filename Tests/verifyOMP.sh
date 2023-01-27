#! /bin/bash
# Verifies that each OpenMP sieve method works correctly by comparing their outputs
# with a known set of primes (0-3Mil).
# 
# Alex Smith (alsmi14@ilstu.edu)
# 8/19/22

# Load the config file.
source .config

# Compile omp driver.
make -s $ompDriver

# Verify that each omp method works correctly.
for serialMethod in 'omp' 'romp' 'romptasks'
do
    # Run the omp sieve up to 3 million.
    $ompDriver 2 2999999 $serialMethod 1>'/dev/null'

    # Compare omp output with Tests/primes_3_million.txt
    diff -w $outPrimes $primes3M 1>'/dev/null'
    error=$?
    if [ $error -ne 0 ]
    then
        echo "$serialMethod Failed."
    else
        echo "$serialMethod Passed."
    fi
done

# Skip a line.
echo ''

# Delete the large primes files.
rm -f $outPrimes