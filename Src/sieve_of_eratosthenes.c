/**
 * @file sieve_of_eratosthenes.c
 * @author Alex Smith (SmithAlexLee30@gmail.com)
 * @brief Implementation file for the Sieve of Eratosthenes library.
 * @date 8/19/2022
 * 
 * @copyright Copyright (c) 2022
 */

#include "sieve_of_eratosthenes.h"

#include <math.h>       // sqrt()
#include <omp.h>        // omp_set_num_threads()
#include <stdlib.h>     // exit(), EXIT_FAILURE
#include <stdio.h>      // fputs(), fprintf()

void serial_init_array(char arr[], unsigned long long size) {
    for (unsigned long long i = 0; i < size; ++i){
        arr[i] = 1;
    }
}

void omp_init_array(char arr[], unsigned long long size) {
    unsigned long long i;
    
    #pragma omp parallel for
    for (i = 0; i < size; ++i){
        arr[i] = 1;
    }
}

void serial_sieve_simple(char primes[], unsigned long long max) {
    // Loop through only the first portion of the array (up to the square root of max).
    unsigned long limit = sqrt((long double) max);

    for (unsigned long i = 2; i <= limit; i++) {
        // If the value is one (true), then it is prime.
        if (primes[i - 1]) {
            // Mark all multiples of the value up to max to zero (false), as they cannot be prime.
            for (unsigned long j = i * i; j <= max; j += i) {
                primes[j - 1] = 0;
            }
        }
    }
}

void serial_sieve_odds(char primes[], unsigned long long max) {
    // Start after 7 because the first 4 entries in the array are always prime.
    if (max > 7) {
        unsigned long i, j, limit = sqrt((long double) max);

        // Loop through only the first portion of the array (up to the square root of max).
        for (i = 3; i <= limit; i += 2) {
            // If the value is one (true), then it is prime.
            if (primes[i / 2]) {
                // Mark all multiples of the value up to max to zero (false), as they cannot be prime.
                for (j = i * i; j <= max; j += 2 * i) {
                    // The multiple is guaranteed to be odd.
                    primes[j / 2] = 0;
                }
            }
        }
    }
}

void serial_rec_sieve_odds(char primes[], unsigned long long max) {
    // Start after 7 because the first 4 entries in the array are always prime.
    if (max > 7) {
        unsigned long long limit = sqrt((long double) max);

        // Loop through only the first portion of the array (up to the square root of max).
        for (unsigned long long i = 3; i <= limit; i += 2) {
            // If the value is one (true), then it is prime.
            if (primes[i / 2]) {
                // Mark all multiples of the value between limit and max to zero (false), as they cannot be prime.
                for (unsigned long long j = i * i; j <= max; j += 2 * i) {
                    // The multiple is guaranteed to be odd.
                    primes[j / 2] = 0;
                }
            }
        }
    }
}

void serial_sieve_1379(char primes[], unsigned long long max) {
    // Start after 7 because the first 4 entries in the array are always prime.
    if (max > 7) {
        unsigned long long i, j, limit = sqrt((long double) max);

        // Loop through only the first portion of the array (up to the square root of max).
        for (i = 3; i <= limit; i += 2) {
            // If the value is one (true), then it is prime.
            if (i != 5 && primes[(unsigned long long) ((i >= 5)? i * 0.4 + 1 : i * 0.4)]) {
                // Mark all multiples of the value up to max to zero (false), as they cannot be prime.
                for (j = i * i; j <= max; j += 2 * i) {
                    // The multiple is guaranteed to be odd.
                    if (j % 5 != 0) {
                        primes[(unsigned long long) ((j >= 5)? j * 0.4 + 1 : j * 0.4)] = 0;
                    }
                }
            }
        }
    }
}

void omp_sieve(char primes[], unsigned long long max) {
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
                    // The multiple is guaranteed to be odd.
                    primes[j / 2] = 0;
                }
            }
        }
    }    
}

void romp_sieve(char primes[], unsigned long long max) {
    // Start after 7 because the first 4 entries in the array are always prime.
    if (max > 7) {
        unsigned long long i, j, limit = sqrt((long double) max);
        romp_sieve(primes, limit);

        // Loop through only the first portion of the array (up to the square root of max).
        #pragma omp parallel private(i)
        {
            for (i = 3; i <= limit; i += 2) {
                // If the value is one (true), then it is prime.
                if (primes[i / 2]) {
                    // Mark all multiples of the value between limit and max to zero (false), as they cannot be prime.
                    #pragma omp for nowait
                    for (j = i * i; j <= max; j += 2 * i) {
                        // The multiple is guaranteed to be odd.
                        primes[j / 2] = 0;
                    }
                }
            }
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
void romp_tasks_sieve_helper(char primes[], unsigned long long max) {
    // Start after 7 because the first 4 entries in the array are always prime.
    if (max > 7) {
        unsigned long long i, j, limit = sqrt((long double) max);
        romp_tasks_sieve_helper(primes, limit);

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

void romp_tasks_sieve(char primes[], unsigned long long max) {
    // Fork a team of threads.
    #pragma omp parallel
    {
        // Have one thread in the team start the method.
        #pragma omp single nowait
        {
            romp_tasks_sieve_helper(primes, max);
        }
    }
}

void write_primes_simple(char *filename, const char primes[], unsigned long long size) {
    // Open output file for writing.
    FILE *outfile;
    if ((outfile = fopen(filename, "w")) == NULL) {
        perror("write_primes_simple");
        exit(EXIT_FAILURE);
    }
    
    // Begin writing.
    for (unsigned long long i = 2; i <= size; i++) {
        if (primes[i - 1]) {
            fprintf(outfile, "%llu\n", i);  
        }
    }

    // Close ouput file.
    fclose(outfile);
}

void write_primes_odds(char *filename, const char primes[], unsigned long long size) {
    // Open output file for writing.
    FILE *outfile;
    if ((outfile = fopen(filename, "w")) == NULL) {
        perror("write_primes_odds");
        exit(EXIT_FAILURE);
    }
    
    // Begin writing.
    if (size >= 1) {
        fputs("2\n", outfile);

        if (size > 1) {
            for (unsigned long long i = 1; i < size; ++i) {
                if (primes[i]) {
                    fprintf(outfile, "%llu\n", i * 2 + 1); 
                }                     
            }                
        }                   
    }

    // Close ouput file.
    fclose(outfile);    
}

void write_primes_1379(char *filename, const char primes[], unsigned long long size) {
    // Open output file for writing.
    FILE *outfile;
    if ((outfile = fopen(filename, "w")) == NULL) {
        perror("write_primes_1379");
        exit(EXIT_FAILURE);
    }
    
    // Begin writing.
    if (size >= 1) {
        fputs("2\n", outfile);

        if (size > 1) {
            fputs("3\n", outfile);

            if (size > 2) {
                fputs("5\n", outfile);

                float offsets[] = {0.5, 1.0, 1.5, 2.0};
                short offIndex = 0;
                for (unsigned long long i = 3; i < size; ++i) {
                    if (primes[i]) {
                        fprintf(outfile, "%llu\n", (unsigned long long) (i * 2.5 - offsets[offIndex])); 
                    }
                    offIndex = (offIndex + 1) % 4;
                }
            }
        }
    }

    // Close ouput file.
    fclose(outfile);
}