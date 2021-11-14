/**
 * This program parallelizes the Sieve of Eratosthenes using MPI to find all primes up to a specified natural number.
 * Based off of code from rbsteinm on GitHub
 * Use -lm to compile!!!
 * @author Katelyn Hartman
 * @date 11/8/21
 */

void printPrimes(const char primes[], unsigned long size);

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

    int nproc; // number of processes
    int my_rank; // rank of the current process
    unsigned long n;
    unsigned long first_elem;
    unsigned long last_elem;
    unsigned long size;
    unsigned long i, k;
    unsigned long index_first_multiple;
    unsigned long next_k;

    MPI_Init(&argc, &argv); // Initialize the MPI environment
    MPI_Comm_size(MPI_COMM_WORLD, &nproc); // Get the number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // Get the rank of the process
    double time = MPI_Wtime();

    if(!(argc == 2))
    {
        if(my_rank == 1) printf("Error: expected 1 or 2 arguments but got %d \n", argc-1);
            exit(1);
    }
    n = atol(argv[1]);

    // we must have that n/nproc > sqrt(n)
    if(!(n/nproc > sqrt(n)))
    {
        if(my_rank == 1)
        {
            printf("Error: there are too many processes! \n");
        }
        MPI_Finalize();
        exit (1);
    }

    // We split the primes into nproc blocks of equal size
    // for each process, get the values of the first and last elems and the number of elems
    first_elem = floor(my_rank*(n-2)/nproc) + 2;
    last_elem = floor((my_rank+1)*(n-2)/nproc) - 1 + 2;
    size = last_elem - first_elem + 1;

    // initialize the primes
    // ignore 0 and 1
    char *primes = malloc(size * sizeof(char));
    for(i = 0; i < size; i++)
    {
        primes[i] = 1; // first every element is marked as prime
    }

    k = 2;

    while(k*k <= n)
    {
        // determine the index of the first multiple of k in the current thread
        if(first_elem % k == 0) index_first_multiple = 0;
        else index_first_multiple = k - first_elem % k;

        // from this first multiple, mark as non-prime every kth element
        for(i = index_first_multiple; i < size; i += k)
        {
            primes[i] = 0;
        }
        if(my_rank == 0) 
        {
            primes[k-2] = 1; 
        }

        // set the next value of k to the smallest prime number > current k
        if(my_rank == 0)
        {
            next_k = k+1;
            while(!primes[next_k - 2])
            {
                next_k = next_k + 1;
            }
            k = next_k; //index to next unmarked value
        }
        //Broadcast k to other threads
        MPI_Bcast (&k,  1, MPI_INT, 0, MPI_COMM_WORLD);
    }

    if(my_rank == 0)
    {
        time = MPI_Wtime() - time;
    }

    printPrimes(primes, size);
    // Finalize the MPI environment.
    MPI_Finalize();
}

/**
 * Prints an primes of primes line-by-line.
 * 
 * @param primes the primes of only odds (except 2) to be printed, where 1 indicates prime and 0 indicates non-prime
 * @param size the number of elements in the primes
 */
void printPrimes(const char primes[], unsigned long size)
{
    if (size >= 1) {
        puts("2");

        if (size > 1) 
            for (int i = 1; i < size; ++i)
                if (primes[i])
                    printf("%d\n", i * 2 + 1);        
    }
}