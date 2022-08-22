# Explaination...
# 
# Alex Smith (alsmi14@ilstu.edu)
# 8/19/22

BIN='Bin'
OUT='Out'
primes3M=$OUT'/primesThrough3Mil.txt'
outPrimes=$OUT'/primes.txt'

# Compile serial driver.
make serialDriver 1>'/dev/null'

# Skip a line.
echo ''

# Verify that each serial method works correctly.
for serialMethod in 'simple' 'odds' 'recursive' '1379'
do
    # Compare serial output with Out/primesThrough3Mil
    "./$BIN/serial_driver" 2999999 $serialMethod 1>'/dev/null'

    diff -w $outPrimes $primes3M 1>/'dev/null'
    error=$?
    if [ $error -ne 0 ]
    then
        echo "$serialMethod Failed."
    else
        echo "$serialMethod Passed."
    fi
done

make clean 1>'/dev/null'