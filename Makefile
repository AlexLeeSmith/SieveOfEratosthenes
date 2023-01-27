# Build file for easily compiling the Sieve of Eratosthenes drivers and cleaning
# all their created files.
# 
# To compile:
# 	make
# 
# Makefile Special Targets: https://www.gnu.org/software/make/manual/html_node/Special-Targets.html
# Makefile Automatic Variables: https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
# 
# Alex Smith (SmithAlexLee30@gmail.com)
# 8/20/22

# Load the config file.
include .config

#### Special Targets ####
.DELETE_ON_ERROR:
.PHONY: all \
		compare compare_omp compare_serial \
		test test_omp test_serial \
		memory \
		clean clean_bin clean_obj clean_out \
		help debug
.SILENT: compare_omp compare_serial \
		 test_omp test_serial \
		 memory \
		 clean clean_bin clean_obj clean_out \
		 help debug

# Directories
BIN := ./Bin
SRC := ./Src
OUT := ./Out

# Filenames
sieve := sieve_of_eratosthenes
serialD := serial_prime_driver
ompD := omp_prime_driver
drivers := $(BIN)/$(serialD) $(BIN)/$(ompD)
objects := $(BIN)/$(sieve).o $(BIN)/$(serialD).o $(BIN)/$(ompD).o

# Libraries
OPENMP := -fopenmp
MATH := -lm

# Other
CC := gcc
RM := rm -f
FLAGS := -g -Wall
SETNAME = -o $@

# Default rule
all: $(drivers)

# Executable rules
$(drivers): %: $(BIN)/$(sieve).o %.o
	$(CC) $(FLAGS) $^ $(SETNAME) $(OPENMP) $(MATH)

# Object rules
$(objects): $(BIN)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(FLAGS) -c $< $(SETNAME) $(OPENMP) $(MATH)

# Cleaning rules
clean: clean_bin clean_primes clean_compare_serial clean_compare_omp

clean_bin:
	$(RM) $(drivers) $(objects)

clean_primes:
	$(RM) $(OUT)/primes.txt

clean_compare_serial:
	$(RM) $(OUT)/compare_serial.txt

clean_compare_omp:
	$(RM) $(OUT)/compare_omp.txt