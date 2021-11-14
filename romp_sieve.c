/**
 * This program parallelizes the Sieve of Eratosthenes recursively using OpenMP to find all primes up to a specified natural number.
 * 
 * @author Alex Smith (alsmi14@ilstu.edu)
 * @date 11/6/21
 */

/** Preprocessor Directives **/
#include <stdio.h>      // printf(), puts(), fprintf(), stderr
#include <math.h>       // sqrt(), ceil()
#include <stdlib.h>     // exit(), EXIT_SUCCESS, EXIT_FAILURE, malloc(), free()
#include <string.h>     // strcmp()
#include <omp.h>        // omp_get_wtime(), omp_set_num_threads(), omp_get_num_procs()

/** Structures **/
typedef struct {
    int numThreads;
    unsigned long long max;
    char shouldPrint;
} myArgs;

/** Functions **/
myArgs getArgs(int, char const *[]);
void usage(const char *);
void ompInitArray(char [], unsigned long long);
void ompSieve(char [], unsigned long long);
void printPrimes(const char [], unsigned long long);

int main(int argc, char const *argv[]) {
    double start, elapsed;
    unsigned long long size;
    char *primes;
    myArgs args;

    // Read command line parameters.
    args = getArgs(argc, argv);

    if (args.max > 1) {
        // Allocate memory.
        size = ceil((double) args.max / 2);
        primes = malloc(size * sizeof(char));

        // Set number of threads to be used.
        omp_set_num_threads(args.numThreads);

        // Initialize primes array.
        start = omp_get_wtime();
        ompInitArray(primes, size);

        // Run the sieve.
        ompSieve(primes, args.max);
        elapsed = omp_get_wtime() - start;
        
        // Output the results.
        printf("R-OMP: %d threads, Max = %.1Le, %f seconds\n", args.numThreads, (long double) args.max, elapsed);
        if (args.shouldPrint)
            printPrimes(primes, size);
    }
    else {
        printf("There are no primes less than %llu\n", args.max);
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
    if (args.numThreads < 1 || args.numThreads > omp_get_num_procs()) 
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
    fprintf(stderr, "\nUsage: %s <thread count> <max> <Opt: 1 to print primes>\n", prog_name);
    fprintf(stderr, "\tThread count must be between 1 and %d\n", omp_get_num_procs());
    fprintf(stderr, "\tMax must be greater than or equal to 0\n\n");
    exit(EXIT_FAILURE);
}

/**
 * Initializes the input array to all 1s using multithreading.
 * 
 * @param arr the array to initialize
 * @param size the size of the array
 */
void ompInitArray(char arr[], unsigned long long size) {
    unsigned long long i;
    
    #pragma omp parallel for
    for (i = 0; i < size; ++i){
        arr[i] = 1;
    }
}

/**
 * Finds all primes up to and including a specifed number using multithreading.
 * 
 * @param primes the array to mark the prime numbers in
 * @param max the largest number to search up to
 */
void ompSieve(char primes[], unsigned long long max) {
    // Start after 7 because the first 4 entries in the array are always prime.
    if (max > 7) {
        unsigned long long i, j, firstJ, jIncrement, limit = sqrt((long double) max) + 1;
        ompSieve(primes, limit);

        // Loop through only the first portion of the array (up to the square root of max).
        #pragma omp parallel private(i, firstJ, jIncrement) if(max - limit >= omp_get_num_threads())
        {
            for (i = 3; i < limit; i += 2) {
                // If the value is one (true), then it is prime.
                if (primes[i / 2]) {
                    // Calculate the first j and ensure it is odd.
                    firstJ = i * (limit / i + 1);
                    if (firstJ % 2 == 0)
                        firstJ += i;
                    
                    // Only calcuate the j-increment once.
                    jIncrement = 2 * i;
                    
                    // Mark all multiples of the value between limit and max to zero (false), as they cannot be prime.
                    #pragma omp for nowait
                    for (j = firstJ; j <= max; j += jIncrement) {
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
void printPrimes(const char primes[], unsigned long long size) {
    if (size >= 1) {
        puts("2");

        if (size > 1) 
            for (unsigned long long i = 1; i < size; ++i)
                if (primes[i])
                    printf("%llu\n", i * 2 + 1);        
    }
}