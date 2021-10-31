#ifndef DFPACK_H
#define DFPACK_H

#include <stdbool.h>

int *dfpack_sieve_of_eratosthenes(int limit, int *num_primes);

bool *dfpack_parallel_sieve_of_eratosthenes(int limit, int *primes_mask_size);

int dfpack_df(int number, int *primes, int num_primes);

int *dfpack_serial_df(int *integers, int max_number, int num_integers);
#endif
