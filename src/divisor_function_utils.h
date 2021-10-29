#ifndef DIVISOR_FUNCTION_UTILS_H
#define DIVISOR_FUNCTION_UTILS_H

bool *divisor_function_utils_sieve_of_eratosthenes(int limit,
                                                    int *primes_mask_size);

bool *divisor_function_utils_parallel_sieve_of_eratosthenes(int limit,
                                                    int *primes_mask_size);
int divisor_function_utils_df(int number, int *primes, int num_primes);


int* divisor_function_utils_serial_df(int *integers, int max_number,int num_integers);
#endif
