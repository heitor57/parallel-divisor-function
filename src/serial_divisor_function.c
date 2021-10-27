#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool *serial_divisor_function_sieve_of_eratosthenes(int limit,
                                                    int *primes_mask_size) {
  *primes_mask_size = limit + 1;
  bool *primes = malloc(*primes_mask_size * sizeof(bool));
  memset(primes, true, *primes_mask_size * sizeof(bool));
  primes[0] = false;
  for (int i = 2; i * i <= limit; i++) {
    if (primes[i] == true) {
      for (int j = i * i; j <= limit; j += i)
        primes[j] = false;
    }
  }
  return primes;
}
/**
 * @brief
 *
 * @param number
 * @param primes
 * @param num_primes
 * @return int
 */
int serial_divisor_function_df(int number, int *primes, int num_primes) {
  int prime, count, num_divisors = 1;
  for (int i = 1; i < num_primes; i++) {
    prime = primes[i];
    /*printf("%d/%d prime %d\n", i, num_primes, prime);*/
    /*fflush(stdout);*/
    count = 0;
    if (number % prime == 0) {
      while (number % prime == 0) {
        number = number / prime;
        count++;
      }
      num_divisors = num_divisors * (count + 1);
    }
  }
  return num_divisors;
}
