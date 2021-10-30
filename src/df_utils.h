#ifndef DF_UTILS_H
#define DF_UTILS_H

#include <stdbool.h>

bool *df_utils_sieve_of_eratosthenes(int limit, int *primes_mask_size);

bool *df_utils_parallel_sieve_of_eratosthenes(int limit, int *primes_mask_size);
int df_utils_df(int number, int *primes, int num_primes);

int *df_utils_serial_df(int *integers, int max_number, int num_integers);
#endif
