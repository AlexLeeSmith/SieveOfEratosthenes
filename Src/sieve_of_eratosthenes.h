/**
 * @file sieve_of_eratosthenes.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-18
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef SIEVE_OF_ERATOSTHENES
#define SIEVE_OF_ERATOSTHENES

/**
 * Initializes the input array to all 1s.
 * 
 * @param arr the array to initialize
 * @param size the size of the array
 */
void serial_init_array(char arr[], unsigned long long size);

/**
 * Initializes the input array to all 1s using multithreading.
 * 
 * @param arr the array to initialize
 * @param size the size of the array
 */
void omp_init_array(char arr[], unsigned long long size);

void serial_sieve_simple(char primes[], unsigned long long max);

void serial_sieve_odds(char primes[], unsigned long long max);

void serial_rec_sieve_odds(char primes[], unsigned long long max);

void serial_sieve_1379(char primes[], unsigned long long max);

/**
 * Finds all primes up to and including a specifed number using multithreading.
 * 
 * @param primes the array to mark the prime numbers in
 * @param max the largest number to search up to
 */
void omp_sieve(char primes[], unsigned long long max);

/**
 * Finds all primes up to and including a specifed number recursively using multithreading.
 * 
 * @param primes the array to mark the prime numbers in
 * @param max the largest number to search up to
 */
void romp_sieve(char primes[], unsigned long long max);

/**
 * Finds all primes up to and including a specifed number recursively with tasks using multithreading.
 * 
 * @param primes the array to mark the prime numbers in
 * @param max the largest number to search up to
 */
void romp_tasks_sieve(char primes[], unsigned long long max);

void write_primes_simple(char *filename, const char primes[], unsigned long long size);

/**
 * Prints an array of primes line-by-line.
 * 
 * @param primes the array of only odds (except 2) to be printed, where 1 indicates prime and 0 indicates non-prime
 * @param size the number of elements in the array
 */
void write_primes_odds(char *filename, const char primes[], unsigned long long size);

void write_primes_1379(char *filename, const char primes[], unsigned long long size);

#endif