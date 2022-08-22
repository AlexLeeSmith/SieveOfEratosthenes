/**
 * @file omp_prime_driver.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-19
 * 
 * @copyright Copyright (c) 2022
 */

#include "sieve_of_eratosthenes.h"
#include "omp_prime_driver.h"

#include <stdio.h>      // printf(), puts(), fprintf(), stderr
#include <math.h>       // sqrt(), ceil()
#include <stdlib.h>     // exit(), EXIT_SUCCESS, EXIT_FAILURE, malloc(), free()
#include <string.h>     // strcmp()
#include <omp.h>        // omp_get_wtime(), omp_set_num_threads(), omp_get_num_procs()

int main(const int argc, char const *argv[]) {
    double start, elapsed;
    unsigned long long size;
    char *primes;
    MyArgs args;

    // Read command line parameters.
    args = get_args(argc, argv);

    if (args.max > 1) {
        // Allocate memory.
        size = ceil((double) args.max / 2);
        primes = malloc(size * sizeof(char));

        // Set number of threads to be used.
        omp_set_num_threads(args.numThreads);

        // Initialize primes array.
        start = omp_get_wtime();
        omp_init_array(primes, size);

        // Run the sieve.
        (*args.sieve_function)(primes, args.max);
        elapsed = omp_get_wtime() - start;
        
        // Output the results.
        printf("%s: %d threads, Max = %.1Le, %f seconds\n", args.functionName, args.numThreads, (long double) args.max, elapsed);

        if (args.shouldWrite) {
            // char filename[20];
            // sprintf(filename, "Out/primes(%s)", args.functionName);
            write_primes_odds("Out/primes.txt", primes, size);
        }         
    }
    else {
        printf("There are no primes less than %llu\n", args.max);
    }
    
    // Free heap memory and exit.
    free(primes);
    exit(EXIT_SUCCESS);
}

MyArgs get_args(const int argc, const char *argv[]) {
    MyArgs args;

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
        args.functionName = "OMP";
        args.sieve_function = &omp_sieve;
    }
    else if (strcmp(argv[3], "romp") == 0 || strcmp(argv[3], "ROMP") == 0) {
        args.functionName = "R_OMP";
        args.sieve_function = &romp_sieve;
    }
    else if (strcmp(argv[3], "romptasks") == 0 || strcmp(argv[3], "ROMPTASKS") == 0) {
        args.functionName = "R_OMP_Tasks";
        args.sieve_function = &romp_tasks_sieve;
    }
    else {
        usage(argv[0]);
    }

    // Verify printing the primes.
    if (argc == 5 && strcmp(argv[4], "0") == 0) {
        args.shouldWrite = 0;
    }
    else {
        args.shouldWrite = 1;
    }
    
    return args;
} 

void usage(const char *progName) {
    fprintf(stderr, "\nUsage: %s [Thread Count] [Max] [Method] [Opt: 0 to not print primes]\n", progName);
    fprintf(stderr, "\t1 <= Thread Count <= %d\n", omp_get_num_procs());
    fprintf(stderr, "\tMax >= 0\n");
    fprintf(stderr, "\tMethods: OMP, ROMP, ROMPTASKS\n\n");
    exit(EXIT_FAILURE);
}