/**
 * This program parallelizes the Sieve of Eratosthenes using OpenMP to find all primes up to a specified natural number.
 * 
 * Usage: %s [Thread Count] [Max] [Method] [Opt: 1 to print primes]
 * Methods: OMP, ROMP, ROMPTASKS
 * 
 * @author Alex Smith (alsmi14@ilstu.edu)
 * @date 12/13/21
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
    char *methodName;
    void (*sieveMethod)(char [], unsigned long long);
    char shouldPrint;
} myArgs;

/** Functions **/
myArgs getArgs(int, char const *[]);
void usage(const char *);
void ompInitArray(char [], unsigned long long);
void ompSieve(char [], unsigned long long);
void rompSieve(char [], unsigned long long);
void rompSieveTasks(char [], unsigned long long);
void rompSieveTasksHelper(char [], unsigned long long);
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
        (*args.sieveMethod)(primes, args.max);
        elapsed = omp_get_wtime() - start;
        
        // Output the results.
        printf("%s: %d threads, Max = %.1Le, %f seconds\n", args.methodName, args.numThreads, (long double) args.max, elapsed);
        if (args.shouldPrint) {
            printPrimes(primes, size);
        }            
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

    // Verify the number of arguments.
    if (argc != 4 && argc != 5) {
        usage(argv[0]);
    }        
    
    // Verify the number of threads.
    args.numThreads = strtol(argv[1], NULL, 10);
    if (args.numThreads < 1 || args.numThreads > omp_get_num_procs()) 
        usage(argv[0]);
    
    // Verify the max.
    if (*argv[2] == '-')
        usage(argv[0]);
    args.max = strtoul(argv[2], NULL, 10);

    // Verify the sieve method.
    if (strcmp(argv[3], "omp") == 0 || strcmp(argv[3], "OMP") == 0) {
        args.methodName = "OMP";
        args.sieveMethod = &ompSieve;
    }
    else if (strcmp(argv[3], "romp") == 0 || strcmp(argv[3], "ROMP") == 0) {
        args.methodName = "R-OMP";
        args.sieveMethod = &rompSieve;
    }
    else if (strcmp(argv[3], "romptasks") == 0 || strcmp(argv[3], "ROMPTASKS") == 0) {
        args.methodName = "R-OMP-Tasks";
        args.sieveMethod = &rompSieveTasks;
    }
    else {
        usage(argv[0]);
    }        

    // Verify printing the primes.
    if (argc == 5 && strcmp(argv[4], "1") == 0) {
        args.shouldPrint = 1;
    }        
    else {
        args.shouldPrint = 0;
    }        
    
    return args;
} 

/**
 * Prints a message to stderr explaining how to run the program.
 * 
 * @param prog_name the name of the executable file
 */
void usage(const char *prog_name) {
    fprintf(stderr, "\nUsage: %s [Thread Count] [Max] [Method] [Opt: 1 to print primes]\n", prog_name);
    fprintf(stderr, "\t1 <= Thread Count <= %d\n", omp_get_num_procs());
    fprintf(stderr, "\tMax >= 0\n");
    fprintf(stderr, "\tMethods: OMP, ROMP, ROMPTASKS\n\n");
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
        unsigned long long i, j, limit = sqrt((long double) max);

        // Loop through only the first portion of the array (up to the square root of max).
        for (i = 3; i <= limit; i += 2) {
            // If the value is one (true), then it is prime.
            if (primes[i / 2]) {
                // Mark all multiples of the value between limit and max to zero (false), as they cannot be prime.
                #pragma omp parallel for
                for (j = i * i; j <= max; j += 2 * i) {
                    // The multiple is guarenteed to be odd.
                    primes[j / 2] = 0;
                }
            }
        }
    }
}

/**
 * Finds all primes up to and including a specifed number recursively using multithreading.
 * 
 * @param primes the array to mark the prime numbers in
 * @param max the largest number to search up to
 */
void rompSieve(char primes[], unsigned long long max) {
    // Start after 7 because the first 4 entries in the array are always prime.
    if (max > 7) {
        unsigned long long i, j, limit = sqrt((long double) max);
        rompSieve(primes, limit);

        // Loop through only the first portion of the array (up to the square root of max).
        #pragma omp parallel private(i) if(max - limit >= omp_get_num_threads())
        {
            for (i = 3; i <= limit; i += 2) {
                // If the value is one (true), then it is prime.
                if (primes[i / 2]) {
                    // Mark all multiples of the value between limit and max to zero (false), as they cannot be prime.
                    #pragma omp for nowait
                    for (j = i * i; j <= max; j += 2 * i) {
                        // The multiple is guarenteed to be odd.
                        primes[j / 2] = 0;
                    }
                }
            }
        }
    }
}

/**
 * Finds all primes up to and including a specifed number recursively with tasks using multithreading.
 * 
 * @param primes the array to mark the prime numbers in
 * @param max the largest number to search up to
 */
void rompSieveTasks(char primes[], unsigned long long max) {
    // Fork a team of threads.
    #pragma omp parallel
    {
        // Have one thread in the team start the method.
        #pragma omp single nowait
        {
            rompSieveTasksHelper(primes, max);
        }
    }
}

/**
 * Helper method for the recursive implementation with tasks. 
 * Do not call this method directly!
 * 
 * @param primes the array to mark the prime numbers in
 * @param max the largest number to search up to
 */
void rompSieveTasksHelper(char primes[], unsigned long long max) {
    // Start after 7 because the first 4 entries in the array are always prime.
    if (max > 7) {
        unsigned long long i, j, limit = sqrt((long double) max);
        rompSieveTasksHelper(primes, limit);

        // Loop through only the first portion of the array (up to the square root of max).
        #pragma omp taskloop
        for (i = 3; i <= limit; i += 2) {
            // If the value is one (true), then it is prime.
            if (primes[i / 2]) {                
                // Mark all multiples of the value between limit and max to zero (false), as they cannot be prime.
                #pragma omp taskloop nogroup
                for (j = i * i; j <= max; j += 2 * i) {
                    primes[j / 2] = 0;
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