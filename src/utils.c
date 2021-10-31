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

int *mask_vector_to_int_vector(bool *v, int size, int *int_vector_size) {
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

int *initial_setup(int argc, char **argv, int *num_integers) {
  int num, i;
  if (argc != 3) {
    printf("Usage:\n");
    printf("%s <input file> <output file>\n", argv[0]);
    printf("Examples:\n");
    printf("%s entrada.txt saida.txt\n",argv[0]);
    printf("%s in.txt out1.txt\n",argv[0]);
    printf("%s in.txt out2.txt\n",argv[0]);
    exit(1);
  }
  char *fin_name = argv[1];
  FILE *fin = fopen(fin_name, "r");
  if (fin == NULL) {
    fprintf(stderr, "Unable to open file %s\n", fin_name);
    exit(1);
  }
  // create integers vector
  int num_lines = file_num_lines(fin);
  int *integers = malloc(sizeof(int) * num_lines);
  // read integers from file
  i = 0;
  while (fscanf(fin, "%d", &num) > 0) {
    integers[i] = num;
    /*printf("%d\n", integers[i]);*/
    i++;
  }
  fclose(fin);
  *num_integers = i;

#ifndef NDEBUG
  printf("%d integers, %d lines\n", *num_integers, num_lines);
#endif

  /**max_number = get_max(integers, *num_integers);*/

/*#ifndef NDEBUG*/
  /*printf("maximum number: %d\n", *max_number);*/
/*#endif*/
  return integers;
}

void write_result(char *fout_name, int *integers_num_divisors,
                  int num_integers) {
  FILE *fout = fopen(fout_name, "w");
  if (fout == NULL) {
    fprintf(stderr, "Unable to open file %s\n", fout_name);
    exit(1);
  }
  for (int i = 0; i < num_integers; i++) {
    fprintf(fout, "%d\n", integers_num_divisors[i]);
  }
  fclose(fout);
}
