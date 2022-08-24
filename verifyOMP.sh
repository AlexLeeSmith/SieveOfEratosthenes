# Explaination...
# 
# Alex Smith (alsmi14@ilstu.edu)
# 8/19/22

BIN='Bin'
OUT='Out'
primes3M=$OUT'/primes_3_million.txt'
outPrimes=$OUT'/primes.txt'

# Compile omp driver.
make ompDriver 1>'/dev/null'

# Skip a line.
echo ''

# Verify that each omp method works correctly.
for serialMethod in 'omp' 'romp' 'romptasks'
do
    # Run the omp sieve up to 3 million.
    "./$BIN/omp_driver" 2 2999999 $serialMethod 1>'/dev/null'

    # Compare omp output with Out/primes_3_million.txt
    diff -w $outPrimes $primes3M 1>'/dev/null'
    error=$?
    if [ $error -ne 0 ]
    then
        echo "$serialMethod Failed."
    else
        echo "$serialMethod Passed."
    fi
done

# Delete just the large primes files.
make clean_primes 1>'/dev/null'