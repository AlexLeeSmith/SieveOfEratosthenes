CC=gcc
MPICC=mpicc
LIBS1=-fopenmp -lm
LIBS2=-lm
BIN=Bin/
OUT=Out/
FLAGS=-g -Wall

all:omp mpi serial

omp:omp_sieve.c
	$(CC) $(FLAGS) -o $(BIN)omp_sieve omp_sieve.c $(LIBS1)

mpi:mpi_sieve.c
	$(MPICC) $(FLAGS) -o $(BIN)mpi_sieve mpi_sieve.c $(LIBS2)

serial:serial_sieve.c
	$(CC) $(FLAGS) -o $(BIN)serial_sieve serial_sieve.c $(LIBS2)

cleanAll:cleanOMP cleanMPI cleanSerial

cleanOMP:
	rm $(BIN)omp_sieve $(OUT)omp_output

cleanMPI:
	rm $(BIN)mpi_sieve $(OUT)mpi_output

cleanSerial:
	rm $(BIN)serial_sieve $(OUT)serial_output