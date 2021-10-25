# SieveOfEratosthenes
In this project we plan on parallelizing the Sieve of Eratosthenes, which is an algorithm for finding prime numbers. This algorithm can be parallelized by having many processors independently mark numbers as composite, resulting in a list of unmarked prime numbers. We will attempt to compare the efficiency of this parallelized algorithm running on both distributed- and shared-memory systems using MPI and OpenMP respectively.

Validate output using:
head -<numPrimes> primesThrough3Mil > <outFile>
diff -w <outFile1> <outFile2>
