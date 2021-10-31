#include "dlinked_list.h"
#include "utils.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#define dfpack_idx_to_value(idx) (idx) * 2 + 1
#define dfpack_value_to_idx(value) ((value)-1) / 2


/**
 * @brief Transform a bool prime vector to a int vector that contains all primes of the bool vector
 *
 * @param primes_mask bool prime mask
 * @param primes_mask_size Mask size
 * @param num_primes Number of primes in the primes mask
 * @return int prime vector
 */
int *dfpack_prime_mask_to_vector(bool *primes_mask, int primes_mask_size,
                                 int num_primes) {
  int *primes = malloc(sizeof(int) * num_primes);
  primes[0] = 2;
  int j = 1;
  for (int i = 0; i < primes_mask_size; i++) {
    if (primes_mask[i]) {
      primes[j] = dfpack_idx_to_value(i);
      j++;
    }
  }
  return primes;
}

/**
 * @brief Sieve of eratosthenes optimized with the removal of even numbers and with fast marking
 *
 * @param limit Number to limit the prime (sieve) search
 * @param num_primes Returns the number of primes found in the given limit
 * @return int vector with the primes found
 */
int *dfpack_sieve_of_eratosthenes(int limit, int *num_primes) {
  int primes_mask_size = (limit + 1) / 2;
  bool *primes_mask = malloc(primes_mask_size * sizeof(bool));
  memset(primes_mask, true, primes_mask_size * sizeof(bool));
  primes_mask[0] = false;
  int prime;
  *num_primes = 0;
  if (limit >= 2) {
    (*num_primes)++;
  }
  int flimit = (int)(dfpack_value_to_idx(sqrt(limit)));
  int i;
  for (i = 1; i <= flimit; i++) {
    if (primes_mask[i] == true) {
      prime = dfpack_idx_to_value(i);
      (*num_primes)++;
      for (int j = i * (2 * i + 2); j < primes_mask_size; j += prime)
        /* Start with prime^2=2*(2*i^2+2*i)+1 and sieve at every double multiple
         * of prime. */
        primes_mask[j] = false;
    }
  }
  while (i < primes_mask_size) {
    if (primes_mask[i]) {
      (*num_primes)++;
    }
    i++;
  }
  int *primes =
      dfpack_prime_mask_to_vector(primes_mask, primes_mask_size, *num_primes);
  free(primes_mask);
  return primes;
}

/**
 * @brief Divisor function, it gives the number of exact divisors of a number
 *
 * @param number Number to found the number of divisors
 * @param primes List of primes to guide the divisors search
 * @param num_primes Number of primes in the vector
 * @return number of divisors of the given number
 */
int dfpack_df(int number, int *primes, int num_primes) {
  int prime, count, num_divisors = 1;
  for (int i = 0; i < num_primes; i++) {
    prime = primes[i];
    count = 0;
    if (number % prime == 0) {
      while (number % prime == 0) {
        number = number / prime;
        count++;
      }
      num_divisors = num_divisors * (count + 1);
    }

    if (prime > sqrt(number)) {
      if (number != 1)
        num_divisors *= 2;
      break;
    }
  }
  return num_divisors;
}


/**
 * @brief Serial divisor implementation, that computes the divisor function for multiple integers
 *
 * @param integers vector of int numbers
 * @param max_number value of the highest int in the vector
 * @param num_integers number of integers in the vector
 * @return list of number of exact divisors of the given integers
 */
int *dfpack_serial_df(int *integers, int max_number, int num_integers) {
  int num_primes;
  int *primes = dfpack_sieve_of_eratosthenes((int)sqrt(max_number), &num_primes);
  int *integers_num_divisors = malloc(num_integers * sizeof(int));
  // not saving directly just to profile only the computation
  for (int i = 0; i < num_integers; i++) {
    integers_num_divisors[i] = dfpack_df(integers[i], primes, num_primes);
#ifndef NDEBUG
    printf("integer: %d, integers_num_divisors: %d\n", integers[i],
           integers_num_divisors[i]);
#endif
  }
  free(primes);
  return integers_num_divisors;
}

