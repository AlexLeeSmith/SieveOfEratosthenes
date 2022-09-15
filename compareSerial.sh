# Runs each serial sieve method with various inputs to compare their runtimes.
# 
# Alex Smith (SmithAlexLee30@gmail.com)
# 8/20/22

# Directories
BIN='./Bin'
OUT='./Out'
outFile="$OUT/compare_serial.txt"
driver="$BIN/serial_prime_driver"

# Compile serial driver.
make -s $driver

# Delete the old compare file if it exists.
make -s clean_compare_serial

# Run the driver for each max and serial sieve method.
for max in 100000000 500000000 # 1e8, 5e8
do
    for serialMethod in 'simple' 'odds' 'recursive' '1379'
    do
        $driver $max $serialMethod 0 >> $outFile
    done
    echo '===============' >> $outFile
done

# Output the location of the comparison file.
echo "Results saved to: $outFile"