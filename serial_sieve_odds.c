/**
 * Serial implementation of the Sieve of Eratosthenes (only odds) for finding all the primes up to a given number.
 * 
 * Usage: ./Bin/serial_sieve_enhanced <max> <Opt: 1 to print result>
 * 
 * @author Alex Smith (alsmi14@ilstu.edu)
 * @date 12/10/21
 */

/** Preprocessor Directives **/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

/** Structures **/
typedef struct {
    unsigned long max;
    char shouldPrint;
} myArgs;

/** Functions **/
myArgs getArgs(int, char const *[]);
void usage(const char *);
void initArray(char [], unsigned long);
void sieve(char [], unsigned long);
double getTime();
void printPrimes(const char [], unsigned long);

int main(int argc, char const *argv[]) {
    double start, elapsed;
    unsigned long size;
    char *primes;
    myArgs args;

    // Validate command line parameters.
    args = getArgs(argc, argv);

    if (args.max > 1) {
        // Allocate memory.
        size = ceil((double) args.max / 2);
        primes = malloc(size * sizeof(char));

        // Initialize primes array.
        start = getTime();
        initArray(primes, size);

        // Run the sieve.
        sieve(primes, args.max);
        elapsed = getTime() - start;
        
        // Output the results.
        printf("Serial-Odds: Max = %.1le, %f seconds\n", (double) args.max, elapsed);
        if (args.shouldPrint)
            printPrimes(primes, size);
    }
    else {
        printf("There are no primes less than %lu\n", args.max);
    }

    exit(EXIT_SUCCESS);
}

/**
 * Get the command line arguments.
 * 
 * @param argc the number of arguments
 * @param argv the array of arguments
 * @return the command line arguments in their correct data types
 */
myArgs getArgs(int argc, char const *argv[]) {
    myArgs args;

    if (argc != 2 && argc != 3) 
        usage(argv[0]);
    
    if (*argv[1] == '-')
        usage(argv[0]);
    args.max = strtoul(argv[1], NULL, 10);
    
    if (argc == 3 && strcmp(argv[2], "1") == 0) 
        args.shouldPrint = 1;
    else
        args.shouldPrint = 0;
    
    return args;
} 

/**
 * Prints a message to stderr explaining how to run the program.
 * 
 * @param prog_name the name of the executable file
 */
void usage(const char *prog_name) {
    fprintf(stderr, "\nUsage: %s <max> <Opt: 1 to print result>\n\n", prog_name);
    exit(EXIT_FAILURE);
}

/**
 * Initializes the input array to all 1s.
 * 
 * @param arr the array to initialize
 * @param size the size of the array
 */
void initArray(char arr[], unsigned long size) {
    for (unsigned long i = 0; i < size; ++i){
        arr[i] = 1;
    }
}

/**
 * Finds all primes up to and including a specifed number.
 * 
 * @param primes the array to mark the prime numbers in
 * @param max the largest number to search up to
 */
void sieve(char primes[], unsigned long max) {
    // Start after 7 because the first 4 entries in the array are always prime.
    if (max > 7) {
        unsigned long i, j, limit = sqrt((long double) max);

        // Loop through only the first portion of the array (up to the square root of max).
        for (i = 3; i <= limit; i += 2) {
            // If the value is one (true), then it is prime.
            if (primes[i / 2]) {
                // Mark all multiples of the value up to max to zero (false), as they cannot be prime.
                for (j = i * i; j <= max; j += 2 * i) {
                    // The multiple is guarenteed to be odd.
                    primes[j / 2] = 0;
                }
            }
        }
    }
}

/**
 * Gets the current time in seconds.
 */
double getTime(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + t.tv_usec/1000000.0;
}

/**
 * Prints an array of primes line-by-line.
 * 
 * @param primes the array of only odds (except 2) to be printed, where 1 indicates prime and 0 indicates non-prime
 * @param size the number of elements in the array
 */
void printPrimes(const char primes[], unsigned long size) {
    if (size >= 1) {
        puts("2");

        if (size > 1) 
            for (unsigned long i = 1; i < size; ++i)
                if (primes[i])
                    printf("%lu\n", i * 2 + 1);        
    }
}