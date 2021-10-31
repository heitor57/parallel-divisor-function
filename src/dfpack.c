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

/*bool *dfpack_parallel_sieve_of_eratosthenes(int limit, int *primes_mask_size)
 * {*/
/**primes_mask_size = limit + 1;*/
/*bool *primes = malloc(*primes_mask_size * sizeof(bool));*/
/*memset(primes, true, *primes_mask_size * sizeof(bool));*/
/*primes[0] = false;*/
/*for (int i = 2; i * i <= limit; i++) {*/
/*if (primes[i] == true) {*/
/*for (int j = i * i; j <= limit; j += i)*/
/*primes[j] = false;*/
/*}*/
/*}*/
/*return primes;*/
/*}*/

int *dfpack_serial_df(int *integers, int max_number, int num_integers) {
  int num_primes;
  int *primes = dfpack_sieve_of_eratosthenes(max_number, &num_primes);
  int *integers_num_divisors = malloc(num_integers * sizeof(int));
  // not saving directly just to profile only the computation
  for (int i = 0; i < num_integers; i++) {
    integers_num_divisors[i] = dfpack_df(integers[i], primes, num_primes);
#ifdef DEBUG
    printf("integer: %d, integers_num_divisors: %d\n", integers[i],
           integers_num_divisors[i]);
#endif
  }
  free(primes);
  return integers_num_divisors;
}

int *dfpack_parallel_sieve_of_eratosthenes(int limit, int *num_primes, int rank,int comm_size) {
  int global_primes_mask_size = (limit + 1) / 2;
  bool *local_primes_mask= NULL;
  int local_primes_mask_size=-1;
  int prime;
  if(!rank){
    int* global_primes_mask = malloc(global_primes_mask_size * sizeof(bool));
    memset(global_primes_mask, true, global_primes_mask_size * sizeof(bool));
    local_primes_mask[0] = false;
    *num_primes = 0;
    if (limit >= 2) {
      (*num_primes)++;
    }
  }
  local_primes_mask_size = BLOCK_SIZE(rank,comm_size,global_primes_mask_size);
  local_primes_mask = malloc(local_primes_mask_size * sizeof(bool));
  memset(local_primes_mask, true, local_primes_mask_size * sizeof(bool));
  int flimit = (int)(dfpack_value_to_idx(sqrt(limit)));
  int i=0;
  int local_num_primes=0;
  int low_value = BLOCK_FLOOR(rank, comm_size, global_primes_mask_size);
  int first;
  do {
    prime = dfpack_idx_to_value(i);
    (*num_primes)++;
    /*dlinked_list_insert_end(li, prime);*/
    if (prime * prime > low_value)
      first = prime * prime - low_value;
    else {
      if (!(low_value % prime)) first = 0;
      else first = prime - (low_value % prime);
    }
    for (int j = i * (2 * i + 2); j < local_primes_mask_size; j += prime)
      local_primes_mask_size[j] = false;
    while (local_primes_mask_size[++i]);
    MPI_Bcast (&prime, 1, MPI_INT, 0, MPI_COMM_WORLD);
    /*for (i = 1; i <= flimit; i++) {*/
    /*if (primes_mask[i] == true) {*/
    /*}*/
    /*}*/
    i++;
  } while (prime * prime <= limit);

  if (!rank) {
    while (i < global_primes_mask_size) {
      if (local_primes_mask[i]) {
        (*num_primes)++;
      }
      i++;
    }
    int *primes =
      dfpack_prime_mask_to_vector(local_primes_mask, global_primes_mask_size, *num_primes);
    free(local_primes_mask);
    return primes;
  }
  return NULL;
}

int *dfpack_parallel_df(int *integers, int max_number, int num_integers,
    int rank) {
  int num_primes;
  int *primes = dfpack_sieve_of_eratosthenes(max_number, &num_primes);
  int *integers_num_divisors = malloc(num_integers * sizeof(int));
  // not saving directly just to profile only the computation
  for (int i = 0; i < num_integers; i++) {
    integers_num_divisors[i] = dfpack_df(integers[i], primes, num_primes);
#ifdef DEBUG
    printf("integer: %d, integers_num_divisors: %d\n", integers[i],
        integers_num_divisors[i]);
#endif
  }
  free(primes);
  return integers_num_divisors;
}
