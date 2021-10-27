#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "serial_divisor_function.h"

int file_num_lines(FILE *f) {
  char c;
  int lines = 0;
  while (!feof(f)) {
    c = fgetc(f);
    if (c == '\n') {
      lines++;
    }
  }
  fseek(f, 0, SEEK_SET);
  return lines;
}

int get_max(int *vector, int num_elements) {

  int max = vector[0];
  for (int i = 1; i < num_elements; i++) {
    if (vector[i] > max) {
      max = vector[i];
    }
  }
  return max;
}

int *mask_vector_to_int_vector(bool *v, int size, int* int_vector_size) {
  int num_true = 0;
  for (int i = 0; i < size; i++) {
    if (v[i] == true) {
      num_true++;
    }
  }
  *int_vector_size = num_true;
  int *iv = malloc(*int_vector_size * sizeof(int));
  int j = 0;
  for (int i = 0; i < size; i++) {
    if (v[i] == true) {
      iv[j] = i;
      j++;
    }
  }
  return iv;
}

int main(int argc, char **argv) {
  int num, i, num_integers;
  char fname[100] = "entrada.txt";
  FILE *file = fopen(fname, "r");
  if (file == NULL) {
    fprintf(stderr, "Unable to open file %s\n", fname);
    return 1;
  }
  int num_lines = file_num_lines(file);
  int *integers = malloc(sizeof(int) * num_lines);
  i = 0;
  while (fscanf(file, "%d", &num) > 0) {
    integers[i] = num;
    /*printf("%d\n", integers[i]);*/
    i++;
  }
  num_integers = i;
  printf("%d integers, %d lines\n", num_integers, num_lines);
  int max_number = get_max(integers, num_integers);
  printf("maximum number: %d\n", max_number);
  int primes_mask_size;
  bool *primes_mask = serial_divisor_function_sieve_of_eratosthenes(
      max_number, &primes_mask_size);
  int num_primes;
  int *primes = mask_vector_to_int_vector(primes_mask, primes_mask_size,&num_primes);
  int num_divisors;
  for (i = 0; i < num_integers; i++) {
    num_divisors =
        serial_divisor_function_df(integers[i], primes, num_primes);
    printf("integer: %d, num_divisors: %d\n", integers[i],num_divisors);
  }
  fclose(file);
  free(integers);
  free(primes);
  free(primes_mask);
  return 0;
}
