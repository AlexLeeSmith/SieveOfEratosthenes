CC=gcc
MPICC=mpicc
LIBS=-fopenmp
BIN=Bin/
OUT=Out/
FLAGS=-g -Wall

all:omp mpi serial

omp:omp_sieve.c
	$(CC) $(FLAGS) -o $(BIN)omp_sieve omp_sieve.c $(LIBS)

mpi:mpi_sieve.c
	$(MPICC) $(FLAGS) -o $(BIN)mpi_sieve mpi_sieve.c

serial:serial_sieve.c
	$(CC) $(FLAGS) -o $(BIN)serial_sieve serial_sieve.c

cleanAll:cleanOMP cleanMPI cleanSerial

cleanOMP:
	rm $(BIN)omp_sieve $(OUT)omp_output

cleanMPI:
	rm $(BIN)mpi_sieve $(OUT)mpi_output

cleanSerial:
	rm $(BIN)serial_sieve $(OUT)serial_output