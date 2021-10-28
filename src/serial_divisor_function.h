#ifndef SERIAL_DIVISOR_FUNCTION_H
#define SERIAL_DIVISOR_FUNCTION_H

bool *serial_divisor_function_sieve_of_eratosthenes(int limit,
                                                    int *primes_mask_size);
int serial_divisor_function_df(int number, int *primes, int num_primes);

#endif
