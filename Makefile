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

# Make directives
.DELETE_ON_ERROR:
.PHONY: all clean clean_bin clean_primes clean_compare_serial clean_compare_omp

# Directories
BIN := ./Bin
SRC := ./Src
OUT := ./Out

# Libraries
OPENMP := -fopenmp
MATH := -lm

# Other
CC := gcc
RM := rm -f
FLAGS := -g -Wall
SETNAME = -o $@

# Filenames
sieve := sieve_of_eratosthenes
serialD := serial_prime_driver
ompD := omp_prime_driver

# Default rule
all: $(BIN)/$(serialD) $(BIN)/$(ompD)

# Executable rules
$(BIN)/$(serialD): $(BIN)/$(sieve).o $(BIN)/$(serialD).o
	$(CC) $(FLAGS) $(BIN)/$(sieve).o $(BIN)/$(serialD).o $(SETNAME) $(OPENMP) $(MATH)

$(BIN)/$(ompD): $(BIN)/$(sieve).o $(BIN)/$(ompD).o
	$(CC) $(FLAGS) $(BIN)/$(sieve).o $(BIN)/$(ompD).o $(SETNAME) $(OPENMP) $(MATH)

# Object rules
$(BIN)/$(sieve).o: $(SRC)/$(sieve).h $(SRC)/$(sieve).c
	$(CC) $(FLAGS) -c $(SRC)/$(sieve).c $(SETNAME) $(OPENMP) $(MATH)

$(BIN)/$(serialD).o: $(SRC)/$(serialD).h $(SRC)/$(serialD).c
	$(CC) $(FLAGS) -c $(SRC)/$(serialD).c $(SETNAME) $(MATH)

$(BIN)/$(ompD).o: $(SRC)/$(ompD).h $(SRC)/$(ompD).c
	$(CC) $(FLAGS) -c $(SRC)/$(ompD).c $(SETNAME) $(OPENMP) $(MATH)

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