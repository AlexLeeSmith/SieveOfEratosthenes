/**
 * This program parallelizes the Sieve of Eratosthenes using OpenMP to find all primes up to a specified natural number.
 * 
 * @author Alex Smith (alsmi14@ilstu.edu)
 * @date 11/6/21
 */

/** Preprocessor Directives **/
#include <stdio.h>      // printf(), puts(), fprintf(), stderr
#include <math.h>       // sqrt()
#include <stdlib.h>     // exit(), EXIT_SUCCESS, EXIT_FAILURE, malloc(), free()
#include <string.h>     // strcmp()
#include <omp.h>        // omp_get_wtime()

#define MAX_THREADS 1024

/** Structures **/
typedef struct {
    int numThreads;
    unsigned long max;
    char shouldPrint;
} myArgs;

/** Functions **/
myArgs getArgs(int, char const *[]);
void usage(const char *);
void ompInitArray(char [], int, unsigned long);
void ompSieve(char [], int, unsigned long);
void printPrimes(const char [], unsigned long);

int main(int argc, char const *argv[]) {
    double start, elapsed;
    unsigned long size;
    char *primes;
    myArgs args;

    // Read command line parameters.
    args = getArgs(argc, argv);

    if (args.max > 1) {
        // Allocate memory.
        size = args.max / 2;
        primes = malloc(size * sizeof(char));

        // Initialize primes array.
        start = omp_get_wtime();
        ompInitArray(primes, args.numThreads, size);

        // Run the sieve.
        ompSieve(primes, args.numThreads, args.max);
        elapsed = omp_get_wtime() - start;
        
        // Output the results.
        printf("R-OMP: %d threads, Max = %lu, %f seconds\n", args.numThreads, args.max, elapsed);
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

    if (argc != 3 && argc != 4) 
        usage(argv[0]);
    
    args.numThreads = strtol(argv[1], NULL, 10);
    if (args.numThreads <= 0 || args.numThreads > MAX_THREADS) 
        usage(argv[0]);
    
    if (*argv[2] == '-')
        usage(argv[0]);
    args.max = strtoul(argv[2], NULL, 10);
    
    if (argc == 4 && strcmp(argv[3], "1") == 0) 
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
    fprintf(stderr, "\nUsage: %s <thread count> <max> <1 to print primes>\n", prog_name);
    fprintf(stderr, "\tThread count must be greater than 0 and less than %d\n", MAX_THREADS + 1);
    fprintf(stderr, "\tMax must be greater than or equal to 0\n\n");
    exit(EXIT_FAILURE);
}

/**
 * Initializes the input array to all 1s using multithreading.
 * 
 * @param arr the array to initialize
 * @param numThreads the number of threads to use
 * @param size the size of the array
 */
void ompInitArray(char arr[], int numThreads, unsigned long size) {
    #pragma omp parallel for num_threads(numThreads)
    for (unsigned long i = 0; i < size; ++i){
        arr[i] = 1;
    }
}

/**
 * Finds all primes up to and including a specifed number using multithreading.
 * 
 * @param primes the array to mark the prime numbers in
 * @param numThreads the number of threads to use
 * @param max the largest number to search up to
 */
void ompSieve(char primes[], int numThreads, unsigned long max) {
    // Start at 3 because primes are non-even except 2.
    if (max > 2) {
        unsigned long i, j, limit = sqrt((long double) max) + 1;
        ompSieve(primes, numThreads, limit);

        // Loop through only the first portion of the array (up to the square root of max).
        #pragma omp parallel private(i) num_threads(numThreads) if(max > 5000)
        {
            for (i = 3; i < limit; i += 2) {
                // If the value is one (true), then it is prime.
                if (primes[i / 2]) {
                    // Mark all multiples of the value to zero (false), as they cannot be prime.
                    #pragma omp for nowait
                    for (j = i * (limit / i + 1); j <= max; j += i) {
                        // Only update the value if it is non-even.
                        if (j % 2 != 0)
                            primes[j / 2] = 0;
                    }
                }
            }
        }
    }
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