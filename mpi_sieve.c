/**
 * This program parallelizes the Sieve of Eratosthenes using MPI to find all primes up to a specified natural number.
 * 
 * @author Katelyn Hartman
 * @date 11/8/21
 */


Skip to content
Pull requests
Issues
Marketplace
Explore
@khartman428
LittleB30 /
SieveOfEratosthenes
Private

1
0

    0

Code
Issues
Pull requests
Actions
Projects
Security

    Insights

SieveOfEratosthenes/romp_sieve.c
@alsmi14
alsmi14 Removed unecessary library
Latest commit a51223c 18 hours ago
History
1 contributor
167 lines (144 sloc) 4.92 KB
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
#include <mpi.h>        // 

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
    int nproc, my_rank;
    char *primes;
    myArgs args;

    // Read command line parameters.
    args = getArgs(argc, argv);

    MPI_Comm comm;
    MPI_Status status;
    
    MPI_Init(&argc,&argv);
    comm=MPI_COMM_WORLD;
    MPI_Comm_size(comm,&nproc);
    MPI_Comm_rank(comm,&my_rank);

    if (args.max > 1) {
        // Allocate memory.
        size = args.max / 2;
        primes = malloc(size * sizeof(char));

        // Initialize primes array.
        MPI_Barrier(comm);
        start = MPI_Wtime();                    
        mpiInitArray(primes, args.numThreads, size);

        // Run the sieve.
        mpiSieve(primes, args.numThreads, size);
        elapsed = MPI_Wtime() - start;
        
        // Output the results.
        printf("MPI: %d threads, Max = %lu, %f seconds\n", args.numThreads, args.max, elapsed);
        if (args.shouldPrint)
            printPrimes(primes, size);
    }
    else {
        printf("There are no primes less than %lu\n", args.max);
    }
    MPI_Finialize()
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
void mpiInitArray(char arr[], int numThreads, unsigned long size) { 
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
void mpiSieve(char primes[], unsigned long size) { 
    for(int i=0; i<size; i++)
    {
        //list created?
        //first prime (k) is 2
        int k = 2;
        //mark all multiples of k between k^2 and n
        //find next unmarked after k, k is now that
        //rank 0 broadcast that number to each process
        //repeat until k^2 > n
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