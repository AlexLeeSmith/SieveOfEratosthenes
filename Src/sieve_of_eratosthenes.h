/**
 * @file sieve_of_eratosthenes.h
 * @author Alex Smith (SmithAlexLee30@gmail.com)
 * @brief Header file for the Sieve of Eratosthenes library.
 * @date 8/19/2022
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef SIEVE_OF_ERATOSTHENES
#define SIEVE_OF_ERATOSTHENES

/**
 * @brief Initializes the input array to all 1s.
 * 
 * @param arr the array to initialize.
 * @param size the size of the array.
 */
void serial_init_array(char arr[], unsigned long long size);

/**
 * @brief Initializes the input array to all 1s using multithreading.
 * 
 * @param arr the array to initialize.
 * @param size the size of the array.
 */
void omp_init_array(char arr[], unsigned long long size);

/**
 * @brief Finds all primes up to and including a specifed number in serial with no optimizations.
 * 
 * @param primes the array to mark the prime numbers in.
 * @param max the largest number to search up to.
 */
void serial_sieve_simple(char primes[], unsigned long long max);

/**
 * @brief Finds all primes up to and including a specifed number in serial while halving the storage requirement.
 * 
 * @param primes the array to mark the prime numbers in.
 * @param max the largest number to search up to.
 */
void serial_sieve_odds(char primes[], unsigned long long max);

/**
 * @brief Finds all primes up to and including a specifed number recursively in serial while halving the storage requirement.
 * 
 * @param primes the array to mark the prime numbers in.
 * @param max the largest number to search up to.
 */
void serial_rec_sieve_odds(char primes[], unsigned long long max);

/**
 * @brief Finds all primes up to and including a specifed number in serial while reducing the storage requirement by 60%.
 * 
 * @param primes the array to mark the prime numbers in.
 * @param max the largest number to search up to.
 */
void serial_sieve_1379(char primes[], unsigned long long max);

/**
 * @brief Finds all primes up to and including a specifed number using multithreading.
 * 
 * @param primes the array to mark the prime numbers in.
 * @param max the largest number to search up to.
 */
void omp_sieve(char primes[], unsigned long long max);

/**
 * Finds all primes up to and including a specifed number recursively using multithreading.
 * 
 * @param primes the array to mark the prime numbers in.
 * @param max the largest number to search up to.
 */
void romp_sieve(char primes[], unsigned long long max);

/**
 * Finds all primes up to and including a specifed number recursively with tasks using multithreading.
 * 
 * @param primes the array to mark the prime numbers in.
 * @param max the largest number to search up to.
 */
void romp_tasks_sieve(char primes[], unsigned long long max);

/**
 * Writes an array of primes line-by-line to file using simple format.
 * 
 * @param primes the array of all numbers (0 -> n-1) to be printed, where 1 indicates prime and 0 indicates non-prime.
 * @param size the number of elements in the array.
 */
void write_primes_simple(char *filename, const char primes[], unsigned long long size);

/**
 * Writes an array of primes line-by-line to file using odds format.
 * 
 * @param primes the array of only odds (except 2) to be printed, where 1 indicates prime and 0 indicates non-prime.
 * @param size the number of elements in the array.
 */
void write_primes_odds(char *filename, const char primes[], unsigned long long size);

/**
 * Writes an array of primes line-by-line to file using 1379 format.
 * 
 * @param primes the array of numbers ending only in 1, 3, 7, or 9 (except 2) to be printed, where 1 indicates prime and 0 indicates non-prime.
 * @param size the number of elements in the array.
 */
void write_primes_1379(char *filename, const char primes[], unsigned long long size);

#endif