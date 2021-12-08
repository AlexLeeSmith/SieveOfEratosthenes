/**
 * This program parallelizes the Sieve of Eratosthenes using MPI to find all primes up to a specified natural number.
 * Based off of code from marius92mc on GitHub
 * use -lm to compile!!!!
 * @author Katelyn Hartman
 * @date 11/8/21
 */

void printPrimes(const char primes[], int size);

#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_FIRST 3 //first odd prime number 
#define BLOCK_STEP 2  //loop step to iterate only for odd numbers
#define MIN(a, b) ((a) < (b)? (a): (b)) //get min
#define BLOCK_LOW(myrank, nproc, n) \
        ((myrank) * (n) / (nproc) / BLOCK_STEP)
#define BLOCK_HIGH(myrank, nproc, n) \
        (BLOCK_LOW((myrank) + 1, nproc, n) - 1)
#define BLOCK_SIZE(myrank, nproc, n) \
        (BLOCK_LOW((myrank) + 1, nproc, n) - BLOCK_LOW((myrank), nproc, n))
#define BLOCK_OWNER(index, nproc, n) \
        (((nproc) * ((index) + 1) - 1) / (n))
#define BLOCK_VALUE_TO_INDEX(val, myrank, nproc, n) \
        (val - BLOCK_FIRST) / BLOCK_STEP - BLOCK_LOW(myrank, nproc, n - 1)

int main(int argc, char** argv)
{
    double  start_time, elapsed_time;           
    int     first;                  //index of first multiple
    int     high_value;             //highest value on this proc
    int     myrank;                 //process myrank number
    int     index;                  //index of current prime
    int     lowVal;                 //lowest value on this proc
    int     i, n, nproc, m, prime, size, sqrt_n;
    int     firstValIn;
    int     primeStep, primeDoub, multiple;
    int     numPerBlock, localLowVal, localHighVal;
    int     blockFirstIn; 
    char*   marked;               //portion of 2 - n
    char*   primes;               //prime array

    MPI_Init(&argc, &argv);

    //get start time
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);

    if (argc != 2)
    {
        if (myrank == 0)
        {
            printf("Command line: %s <m>\n", argv[0]);
        }
        MPI_Finalize();
        exit(1);
    } 

    n = atoi(argv[1]);

    /* 
     * Figure out this process's share of the array, as well as the 
     * integers represented by the first and last array elements 
     */
    lowVal  = BLOCK_FIRST + BLOCK_LOW(myrank, nproc, n - 1)  * BLOCK_STEP;
    high_value = BLOCK_FIRST + BLOCK_HIGH(myrank, nproc, n - 1) * BLOCK_STEP;
    size = BLOCK_SIZE(myrank, nproc, n - 1);

 
    m = (n - 1) / nproc;

    if ((2 + m) < (int)sqrt((double)n))
    {
        if (myrank == 0) 
            printf("Too many processes\n");
        MPI_Finalize();
        exit(1);
    } 
    
    // compute primes from 2 to sqrt(n);
    sqrt_n = sqrt(n);
    primes = (char*)calloc(sqrt_n + 1, 1);
    for (multiple = 2; multiple <= sqrt_n; multiple += 2)
    {
        primes[multiple] = 1;
    }

    for (prime = 3; prime <= sqrt_n; prime += 2)
    {
        if (primes[prime] == 1)
            continue;
        for (multiple = prime << 1;multiple <= sqrt_n; multiple += prime)
        {
            primes[multiple] = 1;
        }
    }

    /* 
     * allocate this process' share of the array 
     */
    marked = (char*)calloc(size * sizeof(char), 1);
    if (marked == NULL)
    {
        printf("Cannot allocate memory\n");
        MPI_Finalize();
        exit(1);
    }

    numPerBlock = 1024 * 1024;
    localLowVal = lowVal;
    localHighVal = MIN(high_value, lowVal + numPerBlock * BLOCK_STEP);
    
    for (blockFirstIn = 0; blockFirstIn < size; blockFirstIn += numPerBlock)
    {
        for (prime = 3; prime <= sqrt_n; prime++)
        {
            if (primes[prime] == 1)
                continue;
            if (prime * prime > localLowVal)
            {
                first = prime * prime;
            }
           else
           {
                if (!(localLowVal % prime))
                {
                    first = localLowVal;
                }
                else
                {
                    first = prime - (localLowVal % prime) + localLowVal;
                }
           }
        
           /*
            * only consider odd multiples of the prime number
            */
           if ((first + prime) & 1) // is odd
           {
              first += prime;
           }

           firstValIn = (first - BLOCK_FIRST) / BLOCK_STEP - BLOCK_LOW(myrank, nproc, n - 1);
           primeDoub = prime << 1;
           primeStep = primeDoub / BLOCK_STEP;
           for (i = first; i <= high_value; i += primeDoub)
           {
               marked[firstValIn] = 1;
               firstValIn += primeStep;
           } 
        }
        
        localLowVal += numPerBlock * BLOCK_STEP;
        localHighVal = MIN(high_value, localHighVal + numPerBlock * BLOCK_STEP); 
    } 


    elapsed_time = MPI_Wtime() - start_time;

    /* print the results */
    printPrimes(primes, size);
    printf("\nElapsed time for %d processors: %d\n", nproc, elapsed_time);
    MPI_Finalize();
    return 0;
}

/**
 * Prints an array of primes line-by-line.
 * 
 * @param primes the array of only odds (except 2) to be printed, where 1 indicates prime and 0 indicates non-prime
 * @param size the number of elements in the array
 */
void printPrimes(const char primes[], int size)
{
    if (size >= 1) {
        puts("2");

        if (size > 1) 
            for (int i = 1; i < size; ++i)
                if (primes[i])
                    printf("%d\n", i * 2 + 1);        
    }
}