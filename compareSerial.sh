# 
# 
# Alex Smith (SmithAlexLee30@gmail.com)
# 8/20/22

BIN='Bin'
OUT='Out'
outFile=$OUT'/compare_serial.txt'

make serialDriver 1>'/dev/null'
make cleanCompareSerial 1>'/dev/null'

# N = 1e7, 1e8
for N in 10000000 100000000
do
    for serialMethod in 'simple' 'odds' 'recursive' '1379'
    do
        "./$BIN/serial_driver" $N $serialMethod 0 >> $outFile
    done
    echo '===============' >> $outFile
done

echo "Results saved to: $outFile"

make cleanSerialDriver 1>'/dev/null'