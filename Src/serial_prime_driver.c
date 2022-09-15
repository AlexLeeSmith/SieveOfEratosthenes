/**
 * @file serial_prime_driver.c
 * @author Alex Smith (SmithAlexLee30@gmail.com)
 * @brief Driver file for running the serial Sieve of Eratosthenes.
 * @date 8/19/2022
 * 
 * @copyright Copyright (c) 2022
 */

#include "sieve_of_eratosthenes.h"
#include "serial_prime_driver.h"

#include <stdio.h>      // printf(), puts(), fprintf(), stderr
#include <math.h>       // sqrt(), ceil()
#include <stdlib.h>     // exit(), EXIT_SUCCESS, EXIT_FAILURE, malloc(), free()
#include <string.h>     // strcmp()
#include <sys/time.h>   // timeval

int main(const int argc, char const *argv[]) {
    double start, elapsed;
    char *primes;
    MyArgs args;

    // Read command line parameters.
    args = get_args(argc, argv);

    if (args.max > 1) {
        // Allocate memory.
        primes = malloc(args.size * sizeof(char));

        // Initialize primes array.
        start = get_time();
        serial_init_array(primes, args.size);

        // Run the sieve.
        (*args.sieve_function)(primes, args.max);
        elapsed = get_time() - start;
        
        // Output the results.
        printf("%s: Max = %.1Le, %f seconds, %llu bytes\n", args.functionName, (long double) args.max, elapsed, args.size);

        if (args.shouldWrite) {
            // char filename[20];
            // sprintf(filename, "Out/primes(%s)", args.functionName);
            (*args.write_function)("Out/primes.txt", primes, args.size);
            printf("Primes have been saved to: %s\n", PRIMES_FILE);
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
    if (argc != 3 && argc != 4) {
        usage(argv[0]);
    }
    
    // Verify the max.
    if (*argv[1] == '-')
        usage(argv[0]);
    args.max = strtoul(argv[1], NULL, 10);

    // Verify the sieve function.
    if (strcmp(argv[2], "simple") == 0 || strcmp(argv[2], "SIMPLE") == 0) {
        args.functionName = "Simple";
        args.sieve_function = &serial_sieve_simple;
        args.write_function = &write_primes_simple;
        args.size = args.max;
    }
    else if (strcmp(argv[2], "odds") == 0 || strcmp(argv[2], "ODDS") == 0) {
        args.functionName = "Odds";
        args.sieve_function = &serial_sieve_odds;
        args.write_function = &write_primes_odds;
        args.size = ceil((long double) args.max / 2);
    }
    else if (strcmp(argv[2], "recursive") == 0 || strcmp(argv[2], "RECURSIVE") == 0) {
        args.functionName = "Recursive";
        args.sieve_function = &serial_rec_sieve_odds;
        args.write_function = &write_primes_odds;
        args.size = ceil((long double) args.max / 2);
    }
    else if (strcmp(argv[2], "1379") == 0) {
        args.functionName = "1379";
        args.sieve_function = &serial_sieve_1379;
        args.write_function = &write_primes_1379;
        args.size = ceil((long double) args.max * 0.4);
        if (args.max >= 5) {
            args.size += 1;
        }
    }
    else {
        usage(argv[0]);
    }  

    // Verify printing the primes.
    if (argc == 4 && strcmp(argv[3], "0") == 0) {
        args.shouldWrite = 0;
    }        
    else {
        args.shouldWrite = 1;
    }    
    
    return args;
} 

void usage(const char *progName) {
    fprintf(stderr, "\nUsage: %s [Max] [Method] [Opt: 0 to not print primes]\n", progName);
    fprintf(stderr, "\tMax >= 0\n");
    fprintf(stderr, "\tMethods: SIMPLE, ODDS, RECURSIVE, 1379\n\n");
    exit(EXIT_FAILURE);
}

double get_time(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + t.tv_usec/1000000.0;
}