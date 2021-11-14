/**
 * This program parallelizes the Sieve of Eratosthenes using OpenMP to find all primes up to a specified natural number.
 * 
 * @author Myesha Choudhury (mkchoud@ilstu.edu)
 * @date 11/8/21
 */

#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc, char* argv[])
{
    unsigned long long i, j; 
    char shouldPrint;
    int numThreads = strtol(argv[1], NULL, 10); 
    unsigned long long lastNum = strtol(argv[2], NULL, 10); 
    unsigned long long size = ceil((double) lastNum / 2);
    unsigned long long lastNumSqrt = sqrt((double)lastNum); 
    char* isPrime = malloc(size * sizeof(char));
    omp_set_num_threads(numThreads);

    if (argc == 4 && strcmp(argv[3], "1") == 0) 
        shouldPrint = 1;
    else
        shouldPrint = 0;

    // initialize array and mark all values as 1
    double start = omp_get_wtime();
    #pragma omp parallel for 
        for(i = 0; i < size; i++)
        {
            isPrime[i] = 1; 
        }
    
    /*
    * Two is the only even prime number 
    * All other primes are odd, so that's why we start at 3 
    * Get the number of threads 
    * If the number is prime set the multiples of it to zero
    */ 
    #pragma omp parallel for private(j)
        for(i = 3; i <= lastNumSqrt; i+=2)
        {
            if(isPrime[i/2])
            {
                for(j = i*i; j <= lastNum; j += 2*i)
                {
                    isPrime[j/2] = 0;
                }
            }
        }
    double elapsed = omp_get_wtime() - start;

    printf("OMP: %d threads, Max = %.1Le, %f seconds\n", numThreads, (long double) lastNum, elapsed);
    if (shouldPrint) {
        if (size >= 1) {
            puts("2");

            if (size > 1) 
                for (i = 1; i < size; ++i)
                    if (isPrime[i])
                        printf("%llu\n", i * 2 + 1);        
        }
        // int found = lastNum >= 2 ? 1 : 0; 
        // #pragma omp parallel for reduction(+:found)
        //     for(i = 1; i <= lastNum; i++)
        //     {
        //         found += isPrime[i]; 
        //     }
        // printf("Last number in range: %d\n", lastNum);
        // printf("Number of primes found: %d\n", found);
    }
    
    free(isPrime);  

    return 0; 
}
