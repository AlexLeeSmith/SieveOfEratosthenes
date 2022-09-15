/**
 * @file serial_prime_driver.h
 * @author Alex Smith (SmithAlexLee30@gmail.com)
 * @brief Header file for a driver that runs the serial Sieve of Eratosthenes.
 * @date 8/19/2022
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef SERIAL_PRIME_DRIVER
#define SERIAL_PRIME_DRIVER

#define PRIMES_FILE "Out/primes.txt"

/**
 * @brief A structure for storing user arguments.
 */
typedef struct {
    /**
     * @brief The value to search for primes up to and including.
     */
    unsigned long long max;

    /**
     * @brief The size of the array that will be required for the chosen sieve function.
     */
    unsigned long long size;

    /**
     * @brief The name of the chosen sieve function.
     */
    char *functionName;

    /**
     * @brief A pointer to the chosen sieve function.
     */
    void (*sieve_function)(char [], unsigned long long);

    /**
     * @brief A pointer to the write function based on the chosen sieve function.
     */
    void (*write_function)(char *, const char [], unsigned long long);

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
 * @return The command line arguments in their correct data types.
 */
MyArgs get_args(const int argc, const char *argv[]);

/**
 * @brief Prints a message to stderr explaining how to run the program.
 * 
 * @param progName the name of the executable file.
 */
void usage(const char *progName);

/**
 * @brief Gets the current time in seconds.
 * 
 * @return The current time in seconds.
 */
double get_time();

#endif