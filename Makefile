# @author Alex Smith (alsmi14@ilstu.edu)
# @date 11/6/21

CC=gcc
RM=rm -f
LIBS1=-fopenmp -lm
LIBS2=-lm
BIN=Bin/
OUT=Out/
FLAGS=-g -Wall

all:omp romp serialSimple serialEnhanced

omp:omp_sieve.c
	$(CC) $(FLAGS) -o $(BIN)omp_sieve omp_sieve.c $(LIBS1)

romp:romp_sieve.c
	$(CC) $(FLAGS) -o $(BIN)romp_sieve romp_sieve.c $(LIBS1)

serialSimple:serial_sieve_simple.c
	$(CC) $(FLAGS) -o $(BIN)serial_sieve_simple serial_sieve_simple.c $(LIBS2)

serialEnhanced:serial_sieve_enhanced.c
	$(CC) $(FLAGS) -o $(BIN)serial_sieve_enhanced serial_sieve_enhanced.c $(LIBS2)

clean:cleanOMP cleanROMP cleanSerialSimple cleanSerialEnhanced cleanCompareSerial cleanCompareParallel cleanVerify

cleanOMP:
	$(RM) $(BIN)omp_sieve

cleanROMP:
	$(RM) $(BIN)romp_sieve

cleanSerialSimple:
	$(RM) $(BIN)serial_sieve_simple

cleanSerialEnhanced:
	$(RM) $(BIN)serial_sieve_enhanced

cleanCompareSerial:cleanSerialSimple cleanSerialEnhanced cleanOMP cleanROMP
	$(RM) $(OUT)compare_serial_output

cleanCompareParallel:cleanOMP cleanROMP
	$(RM) $(OUT)compare_parallel_output

cleanVerify:
	$(RM) $(OUT)verify_even $(OUT)verify_odd