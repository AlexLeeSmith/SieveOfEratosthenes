CC=gcc
MPICC=mpicc
RM=rm -f
LIBS1=-fopenmp -lm
LIBS2=-lm
BIN=Bin/
OUT=Out/
FLAGS=-g -Wall

all:romp mpi serialSimple

romp:romp_sieve.c
	$(CC) $(FLAGS) -o $(BIN)romp_sieve romp_sieve.c $(LIBS1)

mpi:mpi_sieve.c
	$(MPICC) $(FLAGS) -o $(BIN)mpi_sieve mpi_sieve.c $(LIBS2)

serialSimple:serial_sieve_simple.c
	$(CC) $(FLAGS) -o $(BIN)serial_sieve_simple serial_sieve_simple.c $(LIBS2)

clean:cleanROMP cleanMPI cleanSerialSimple cleanVerify

cleanROMP:
	$(RM) $(BIN)romp_sieve $(OUT)romp_output

cleanMPI:
	$(RM) $(BIN)mpi_sieve $(OUT)mpi_output

cleanSerialSimple:
	$(RM) $(BIN)serial_sieve_simple $(OUT)serial_simple_output

cleanVerify:
	$(RM) $(OUT)verify_parallel_even $(OUT)verify_parallel_odd