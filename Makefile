# @author Alex Smith (alsmi14@ilstu.edu)
# @date 11/6/21

CC=gcc
RM=rm -f
LIBS1=-fopenmp -lm
LIBS2=-lm
BIN=Bin/
OUT=Out/
FLAGS=-g -Wall

all:omp serialSimple serialEnhanced

omp:omp_sieve.c
	$(CC) $(FLAGS) -o $(BIN)omp_sieve omp_sieve.c $(LIBS1)

serialSimple:serial_sieve_simple.c
	$(CC) $(FLAGS) -o $(BIN)serial_sieve_simple serial_sieve_simple.c $(LIBS2)

serialEnhanced:serial_sieve_enhanced.c
	$(CC) $(FLAGS) -o $(BIN)serial_sieve_enhanced serial_sieve_enhanced.c $(LIBS2)

clean:cleanOMP cleanSerialSimple cleanSerialEnhanced cleanCompareSerial cleanCompareParallel cleanVerify

cleanOMP:
	$(RM) $(BIN)omp_sieve

cleanSerialSimple:
	$(RM) $(BIN)serial_sieve_simple

cleanSerialEnhanced:
	$(RM) $(BIN)serial_sieve_enhanced

cleanCompareSerial:cleanSerialSimple cleanSerialEnhanced cleanOMP
	$(RM) $(OUT)compare_serial_output

cleanCompareParallel:cleanOMP
	$(RM) $(OUT)compare_parallel_output

cleanVerify:
	$(RM) $(OUT)verify_even $(OUT)verify_odd