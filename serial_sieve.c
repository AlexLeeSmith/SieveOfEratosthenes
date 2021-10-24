/**
 * Implementation of the sieve of Eratosthenes for finding all the primes up to a given number.
 * Edited to allow for command line arguments.
 * 
 * Source: https://gist.github.com/mcmullm2-dcu/117649ca592b8d6a065aa28db41b11dd 
 * 
 * @author Michael McMullin
 * @date 2/6/18
 */

#include <stdio.h>
#include <math.h>

#define MAX 1000000

int main(int argc, char const *argv[]) {
    // Create an array of values, where '1' indicates that a number is prime.
    // Start by assuming all numbers are prime by setting them to 1.
    char primes[MAX];
    for (int i = 0; i < MAX; i++){
        primes[i] = 1;
    }

    // Loop through a portion of the array (up to the square root of MAX).
    // If it's a prime, ensure all multiples of it are set to zero (false), as they clearly cannot be prime.
    int limit = sqrt(MAX) + 1;
    for (int i = 2; i < limit; i++) {
        if (primes[i - 1]) {
            for (int j = i * i; j <= MAX; j += i) {
                primes[j - 1] = 0;
            }
        }
    }

    // Output the results.
    int count = 0;
    for (int i = 2; i <= MAX; i++) {
        if (primes[i - 1]) {
            printf("%d\n", i);
            count++;
        }
    }
    printf("There were %d primes up to %d", count, MAX);

    return 0;
}