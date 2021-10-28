#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#include "serial_divisor_function.h"


int main(int argc, char **argv) {
  int num, i, num_integers;
  char* input_file_name = argv[1];
  char* output_file_name = argv[2];
  FILE *input_file = fopen(input_file_name, "r");
  if (input_file == NULL) {
    fprintf(stderr, "Unable to open file %s\n", input_file_name);
    return 1;
  }
  // create integers vector
  int num_lines = file_num_lines(input_file);
  int *integers = malloc(sizeof(int) * num_lines);
  // read integers from file
  i = 0;
  while (fscanf(input_file, "%d", &num) > 0) {
    integers[i] = num;
    /*printf("%d\n", integers[i]);*/
    i++;
  }
  fclose(input_file);
  num_integers = i;

#ifdef DEBUG
  printf("%d integers, %d lines\n", num_integers, num_lines);
#endif

  int max_number = get_max(integers, num_integers);

#ifdef DEBUG
  printf("maximum number: %d\n", max_number);
#endif

  int primes_mask_size;
  bool *primes_mask = serial_divisor_function_sieve_of_eratosthenes(
      max_number, &primes_mask_size);
  int num_primes;
  int *primes = mask_vector_to_int_vector(primes_mask, primes_mask_size,&num_primes);
  int *num_divisors= malloc(num_integers*sizeof(int));
  // not saving directly just to profile only the computation
  for (i = 0; i < num_integers; i++) {
    num_divisors[i] =
        serial_divisor_function_df(integers[i], primes, num_primes);
#ifdef DEBUG
    printf("integer: %d, num_divisors: %d\n", integers[i],num_divisors[i]);
#endif
  }

  FILE* output_file = fopen(output_file_name, "w");
  for (i = 0; i < num_integers; i++) {
    fprintf(output_file, "%d\n",num_divisors[i]);
  }
  free(num_divisors);
  free(integers);
  free(primes);
  free(primes_mask);
  return 0;
}
