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
#### Testing Rules ####
test: test_omp test_serial

test_omp:
	$(TEST)/verifyOMP.sh

test_serial:
	$(TEST)/verifySerial.sh

compare: compare_omp compare_serial

compare_omp:
	$(TEST)/compareOMP.sh

compare_serial:
	$(TEST)/compareSerial.sh

# Executable rules
$(drivers): %: $(BIN)/$(sieve).o %.o
	$(CC) $(FLAGS) $^ $(SETNAME) $(OPENMP) $(MATH)

# Object rules
$(objects): $(BIN)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(FLAGS) -c $< $(SETNAME) $(OPENMP) $(MATH)

#### Cleaning Rules ####
clean: clean_bin clean_obj clean_out
	echo "Directories have been cleaned.\n"

clean_bin:
	$(RM) $(BINS)

clean_obj:
	$(RM) $(OBJS) $(DEPS)

clean_out:
	$(RM) $(outPrimes) $(outSerialCompare) $(outSerialMemory) $(outOmpCompare) $(outOmpMemory)

clean_compare_serial:
	$(RM) $(OUT)/compare_serial.txt

clean_compare_omp:
	$(RM) $(OUT)/compare_omp.txt