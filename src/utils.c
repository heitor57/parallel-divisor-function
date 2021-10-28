#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
