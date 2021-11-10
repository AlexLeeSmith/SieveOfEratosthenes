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

compareSerial:serialSimple serialEnhanced

serialSimple:serial_sieve_simple.c
	$(CC) $(FLAGS) -o $(BIN)serial_sieve_simple serial_sieve_simple.c $(LIBS2)

serialEnhanced:serial_sieve_enhanced.c
	$(CC) $(FLAGS) -o $(BIN)serial_sieve_enhanced serial_sieve_enhanced.c $(LIBS2)

clean:cleanROMP cleanMPI cleanSerialSimple cleanSerialEnhanced cleanVerify

cleanROMP:
	$(RM) $(BIN)romp_sieve $(OUT)romp_output

cleanMPI:
	$(RM) $(BIN)mpi_sieve $(OUT)mpi_output

cleanSerialSimple:
	$(RM) $(BIN)serial_sieve_simple $(OUT)serial_simple_output

cleanSerialEnhanced:
	$(RM) $(BIN)serial_sieve_enhanced $(OUT)serial_enhanced_output

cleanCompareSerial:
	$(RM) $(BIN)serial_sieve_simple $(BIN)serial_sieve_enhanced $(OUT)compare_serial_output

cleanVerify:
	$(RM) $(OUT)verify_even $(OUT)verify_odd