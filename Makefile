# Build file for easily compiling the Sieve of Eratosthenes drivers and cleaning
# all their created files.
# 
# To compile:
# 	make
# 
# To delete all generated files:
# 	make clean
# 
# Alex Smith (SmithAlexLee30@gmail.com)
# 8/20/22

# Directories
BIN=Bin
SRC=Src
OUT=Out

# Libraries
OPENMP=-fopenmp
MATH=-lm

# Other
CC=gcc
RM=rm -f
FLAGS=-c -g -Wall

# Filenames
sieve=sieve_of_eratosthenes
serialD=serial_prime_driver
ompD=omp_prime_driver

# Default rule
all: $(BIN)/$(serialD) $(BIN)/$(ompD)

# Executable rules
$(BIN)/$(serialD): $(BIN)/$(sieve).o $(BIN)/$(serialD).o
	$(CC) $(BIN)/$(sieve).o $(BIN)/$(serialD).o -o $@ $(OPENMP) $(MATH)

$(BIN)/$(ompD): $(BIN)/$(sieve).o $(BIN)/$(ompD).o
	$(CC) $(BIN)/$(sieve).o $(BIN)/$(ompD).o -o $@ $(OPENMP) $(MATH)

# Object rules
$(BIN)/$(sieve).o: $(SRC)/$(sieve).h $(SRC)/$(sieve).c
	$(CC) $(FLAGS) $(SRC)/$(sieve).c -o $@ $(OPENMP) $(MATH)

$(BIN)/$(serialD).o: $(SRC)/$(serialD).h $(SRC)/$(serialD).c
	$(CC) $(FLAGS) $(SRC)/$(serialD).c -o $@ $(MATH)

$(BIN)/$(ompD).o: $(SRC)/$(ompD).h $(SRC)/$(ompD).c
	$(CC) $(FLAGS) $(SRC)/$(ompD).c -o $@ $(OPENMP) $(MATH)

# Cleaning rules
clean: clean_bin clean_primes clean_compare_serial clean_compare_omp

clean_bin:
	$(RM) $(BIN)/$(serialD) $(BIN)/$(ompD) $(BIN)/*.o

clean_primes:
	$(RM) $(OUT)/primes.txt

clean_compare_serial:
	$(RM) $(OUT)/compare_serial.txt

clean_compare_omp:
	$(RM) $(OUT)/compare_omp.txt