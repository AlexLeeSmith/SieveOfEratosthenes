# @author Alex Smith (alsmi14@ilstu.edu)
# @date 11/6/21

CC=gcc
RM=rm -f
LIBS1=-fopenmp -lm
LIBS2=-lm
BIN=Bin/
OUT=Out/
FLAGS=-g -Wall

all:omp serialSimple serialOdds serial1379

omp:omp_sieve.c
	$(CC) $(FLAGS) -o $(BIN)omp_sieve omp_sieve.c $(LIBS1)

serialSimple:serial_sieve_simple.c
	$(CC) $(FLAGS) -o $(BIN)serial_sieve_simple serial_sieve_simple.c $(LIBS2)

serialOdds:serial_sieve_odds.c
	$(CC) $(FLAGS) -o $(BIN)serial_sieve_odds serial_sieve_odds.c $(LIBS2)

serial1379:serial_sieve_1379.c
	$(CC) $(FLAGS) -o $(BIN)serial_sieve_1379 serial_sieve_1379.c $(LIBS2)

clean:cleanOMP cleanSerialSimple cleanSerialOdds cleanSerial1379 cleanCompareSerial cleanCompareParallel cleanVerify

cleanOMP:
	$(RM) $(BIN)omp_sieve

cleanSerialSimple:
	$(RM) $(BIN)serial_sieve_simple

cleanSerialOdds:
	$(RM) $(BIN)serial_sieve_odds

cleanSerial1379:
	$(RM) $(BIN)serial_sieve_1379

cleanCompareSerial:cleanSerialSimple cleanSerialOdds cleanSerial1379 cleanOMP
	$(RM) $(OUT)compare_serial_output

cleanCompareParallel:cleanOMP
	$(RM) $(OUT)compare_parallel_output

cleanVerify:
	$(RM) $(OUT)verify_even $(OUT)verify_odd