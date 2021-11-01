#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>
#include <stdio.h>
int get_max(int *vector, int num_elements);
int file_num_lines(FILE *f);
int *initial_setup(int argc, char **argv, int *num_integers);
void write_result(char *output_file_name, int *integers_num_divisors,
                  int num_integers);
#endif
