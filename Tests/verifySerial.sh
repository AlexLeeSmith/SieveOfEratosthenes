#! /bin/bash
# Verifies that each serial sieve method works correctly by comparing their outputs
# with a known set of primes (0-3Mil).
# 
# Alex Smith (alsmi14@ilstu.edu)
# 8/19/22

# Load the config file.
source .config

# Compile serial driver.
make -s $serialDriver

# Verify that each serial method works correctly.
for serialMethod in 'simple' 'odds' 'recursive' '1379'
do
    # Run the serial sieve up to 3 million.
    $serialDriver 2999999 $serialMethod 1>'/dev/null'

    # Compare serial output with Tests/primes_3_million.txt
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