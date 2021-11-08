/**
 * Implementation of the sieve of Eratosthenes for finding all the primes up to a given number.
 * Edited to allow for command line arguments and timing.
 * 
 * Source: https://gist.github.com/mcmullm2-dcu/117649ca592b8d6a065aa28db41b11dd 
 * Usage: ./Bin/serial_sieve_simple <max> <Opt: 1 to print result>
 * 
 * @author Michael McMullin
 * @date 2/6/18
 * @editor Alex Smith (alsmi14@ilstu.edu)
 * @editdate 10/24/21
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void usage(const char *);
double getTime();

int main(int argc, char const *argv[]) {
    // Validate command line parameters.
    if (argc != 2 && argc != 3) 
        usage(argv[0]);
    
    // Read command line parameters.
    long max = atol(argv[1]);
    char *primes = malloc(max * sizeof(char));
    char shouldPrint;
    if (argc == 3 && strcmp(argv[2], "1") == 0) 
        shouldPrint = 1;
    else
        shouldPrint = 0;

    // Create an array of values, where '1' indicates that a number is prime.
    // Start by assuming all numbers are prime by setting them to 1.
    double start = getTime();
    for (long i = 0; i < max; i++){
        primes[i] = 1;
    }

    // Loop through a portion of the array (up to the square root of max).
    // If it's a prime, ensure all multiples of it are set to zero (false), as they clearly cannot be prime.
    long limit = sqrt((long double) max) + 1;
    for (long i = 2; i < limit; i++) {
        if (primes[i - 1]) {
            for (long j = i * i; j <= max; j += i) {
                primes[j - 1] = 0;
            }
        }
    }
    double elapsed = getTime() - start;

    // Output the results.
    printf("Serial-Simple: Max = %ld, %f seconds\n", max, elapsed);
    if (shouldPrint) {
        for (long i = 2; i <= max; i++) {
            if (primes[i - 1]) {
                printf("%ld\n", i);
            }
        }
    }

    exit(EXIT_SUCCESS);
}

/**
 * Prints a message to stderr explaining how to run the program.
 * 
 * @param prog_name the name of the executable file
 */
void usage(const char *prog_name) {
    fprintf(stderr, "\nUsage: %s <max> <1 to print result>\n\n", prog_name);
    exit(EXIT_FAILURE);
}

/**
 * Gets the current time in seconds.
 */
double getTime(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec + t.tv_usec/1000000.0;
}