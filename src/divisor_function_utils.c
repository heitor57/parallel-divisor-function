#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool *divisor_function_utils_sieve_of_eratosthenes(int limit,
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
int divisor_function_utils_df(int number, int *primes, int num_primes) {
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


bool *divisor_function_utils_parallel_sieve_of_eratosthenes(int limit,
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


int* serial_df(int *integers, int max_number,int num_integers){
  int primes_mask_size;
  bool *primes_mask = divisor_function_utils_sieve_of_eratosthenes(
      max_number, &primes_mask_size);
  int num_primes;
  int *primes = mask_vector_to_int_vector(primes_mask, primes_mask_size,&num_primes);
  int *integers_num_divisors= malloc(num_integers*sizeof(int));
  // not saving directly just to profile only the computation
  for (int i = 0; i < num_integers; i++) {
    integers_num_divisors[i] =
        divisor_function_utils_df(integers[i], primes, num_primes);
#ifdef DEBUG
    printf("integer: %d, integers_num_divisors: %d\n", integers[i],integers_num_divisors[i]);
#endif
  }
  free(primes_mask);
  free(primes);
  return integers_num_divisors;
}
