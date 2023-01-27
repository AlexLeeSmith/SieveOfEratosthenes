#! /bin/bash
# Runs each serial sieve method with various inputs to compare their runtimes.
# 
# Alex Smith (SmithAlexLee30@gmail.com)
# 8/20/22

# Load the config file.
source .config

# Compile serial driver.
make -s $serialDriver

# Delete the old compare file if it exists.
rm -f $outSerialCompare

# Output start prompt.
echo -n "Comparing serial..."

# Run the driver for each max and serial sieve method.
for max in 100000000 500000000 # 1e8, 5e8
do
    for serialMethod in 'simple' 'odds' 'recursive' '1379'
    do
        $serialDriver $max $serialMethod 0 >> $outSerialCompare
    done
    echo '===============' >> $outSerialCompare
done

# Output the location of the comparison file.
echo -e "\rSerial results saved to: $outSerialCompare"