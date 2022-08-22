/**
 * @file prime_driver.h
 * @author Alex Smith (SmithAlexLee30@gmail.com)
 * @brief Header file for a driver that runs the OpenMP Sieve of Eratosthenes.
 * @date 8/19/2022
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef OMP_PRIME_DRIVER
#define OMP_PRIME_DRIVER

/**
 * @brief A structure for storing user arguments.
 */
typedef struct {
    /**
     * @brief The number of threads to perform the calculation with.
     */
    int numThreads;

    /**
     * @brief The value to search for primes up to and including.
     */
    unsigned long long max;

    /**
     * @brief The name of the chosen sieve function.
     */
    char *functionName;

    /**
     * @brief A pointer to the chosen sieve function.
     */
    void (*sieve_function)(char [], unsigned long long);

    /**
     * @brief A boolean to specify if the calculated primes should be written to file.
     */
    char shouldWrite;
} MyArgs;

/**
 * @brief Get the command-line arguments.
 * 
 * @param argc the number of arguments.
 * @param argv the array of arguments.
 * @return MyArgs - the command line arguments in their correct data types.
 */
MyArgs get_args(const int argc, const char *argv[]);

/**
 * @brief Prints a message to stderr explaining how to run the program.
 * 
 * @param progName the name of the executable file.
 */
void usage(const char *progName);

#endif