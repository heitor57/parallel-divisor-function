#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#include "divisor_function_utils.h"

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

int main(int argc, char **argv) {
  int max_number,num_integers;
  int *integers;
  integers =initial_setup(argc,argv,&max_number,&num_integers);
  int * integers_num_divisors= serial_df(integers, max_number, num_integers);
  write_result(argv[2], integers_num_divisors, num_integers);

  free(integers_num_divisors);
  free(integers);
  free(integers_num_divisors);
  return 0;
}
