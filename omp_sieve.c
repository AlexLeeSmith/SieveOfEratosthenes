#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
int main(int argc, char* argv[])
{
    int i, j; 
    int numThreads; 
    omp_set_num_threads(atoi(argv[1]));
    int lastNum = atoi(argv[2]); 
    const int lastNumSqrt = (int)sqrt((double)lastNum); 
    char* isPrime = malloc(lastNum + 1 * sizeof(int)); 

    // initialize array and mark all values as 1
    #pragma omp parallel for 
        for(int i = 0; i <= lastNum; i++)
        {
            isPrime[i] = 1; 
        }
    /*
    * Two is the only even prime number 
    * All other primes are odd, so that's why we start at 3 
    * Get the number of threads 
    * If the number is prime set the multiples of it to zero
    */ 
    double start = omp_get_wtime();
    #pragma omp parallel for private(j)
        for(i = 3; i <= lastNumSqrt; i+=2)
        {
            numThreads = omp_get_num_threads(); 
            if(isPrime[i/2])
            {
                for(j = i*i; j <= lastNum; j += 2*i)
                {
                    isPrime[j/2] = 0;
                }
            }
        }

    int found = lastNum >= 2 ? 1 : 0; 
    #pragma omp parallel for reduction(+:found)
        for(i = 1; i <= lastNum; i++)
        {
            found += isPrime[i]; 
        }
    double elasped = omp_get_wtime() - start;
    printf("Last number in range: %d\n", lastNum);
    printf("Number of threads: %d\n", numThreads);
    printf("Number of primes found: %d\n", found);  
    printf("Elapsed time: %f\n", elasped); 
    free(isPrime);  

    return 0; 
}
