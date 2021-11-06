/**
 * This program parallelizes the Sieve of Eratosthenes using OpenMP to find all primes up to a specified natural number.
 * 
 * @author Alex Smith (alsmi14@ilstu.edu)
 * @date 11/6/21
 */

/** Preprocessor Directives **/
#include <stdio.h>      // printf(), fprintf(), stderr, perror()
#include <math.h>       // sqrt()
#include <stdlib.h>     // exit(), EXIT_SUCCESS, EXIT_FAILURE, malloc(), free()
#include <string.h>     // strcmp()
#include <sys/time.h>   // timeval, gettimeofday()
#include <omp.h>        // omp_get_wtime()

#define MAX_THREADS 1024

/** Structures **/
typedef struct {
    int numThreads;
    unsigned long max;
    char shouldPrint;
} myArgs;

/** Functions **/
myArgs getArgs(int, char *[]);
void usage(const char *);
void ompInitArray(char [], int, unsigned long);
void ompSieve(char [], int, unsigned long);

int main(int argc, char const *argv[]) {
    double start, elapsed;
    unsigned long primeCount = 0, size;
    char *primes;
    myArgs args;

    // Read command line parameters.
    args = getArgs(argc, argv);

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
    printf("R-OMP: %lu primes up to %lu and took %f seconds\n", primeCount, args.max, elapsed);
    exit(EXIT_SUCCESS);
}

/**
 * Get the command line arguments.
 * 
 * @param argc the number of arguments
 * @param argv the array of arguments
 * @return the command line arguments in their correct data types
 */
myArgs getArgs(int argc, char *argv[]) {
    myArgs args;
    
    if (argc != 3 && argc != 4) 
        usage(argv[0]);
    
    args.numThreads = strtol(argv[1], NULL, 10);
    if (args.numThreads <= 0 || args.numThreads > MAX_THREADS) 
        usage(argv[0]);
    
    args.max = strtoul(argv[2], NULL, 10);
    if (args.max == 0)
        usage(argv[0]);

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
    fprintf(stderr, "\tMax must be greater than 0\n\n");
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
    for (unsigned long i = 0; i < size; i++){
        arr[i] = 1;
    }
}

/**
 * Finds all primes up to a specifed number using multithreading.
 * 
 * @param primes the array to mark the prime numbers in
 * @param numThreads the number of threads to use
 * @param max the largest number to search up to
 */
void ompSieve(char primes[], int numThreads, unsigned long max) {

}