CC=gcc
MPICC=mpicc
RM=rm -f
LIBS1=-fopenmp -lm
LIBS2=-lm
BIN=Bin/
OUT=Out/
FLAGS=-g -Wall

all:romp mpi serialSimple serialEnhanced

romp:romp_sieve.c
	$(CC) $(FLAGS) -o $(BIN)romp_sieve romp_sieve.c $(LIBS1)

mpi:mpi_sieve.c
	$(MPICC) $(FLAGS) -o $(BIN)mpi_sieve mpi_sieve.c $(LIBS2)

serialSimple:serial_sieve_simple.c
	$(CC) $(FLAGS) -o $(BIN)serial_sieve_simple serial_sieve_simple.c $(LIBS2)

serialEnhanced:serial_sieve_enhanced.c
	$(CC) $(FLAGS) -o $(BIN)serial_sieve_enhanced serial_sieve_enhanced.c $(LIBS2)

clean:cleanROMP cleanMPI cleanSerialSimple cleanSerialEnhanced cleanCompareSerial cleanVerify

cleanROMP:
	$(RM) $(BIN)romp_sieve

cleanMPI:
	$(RM) $(BIN)mpi_sieve

cleanSerialSimple:
	$(RM) $(BIN)serial_sieve_simple

cleanSerialEnhanced:
	$(RM) $(BIN)serial_sieve_enhanced

cleanCompareSerial:cleanSerialSimple cleanSerialEnhanced cleanROMP
	$(RM) $(OUT)compare_serial_output

cleanCompareParallel:cleanROMP
	$(RM) $(OUT)compare_parallel_output

cleanVerify:
	$(RM) $(OUT)verify_even $(OUT)verify_odd