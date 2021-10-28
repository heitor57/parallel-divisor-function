#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
int *mask_vector_to_int_vector(bool *v, int size, int *int_vector_size);
int get_max(int *vector, int num_elements);
int file_num_lines(FILE *f);
#endif
