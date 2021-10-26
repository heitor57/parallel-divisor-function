#include <stdio.h>
#include <stdlib.h>

int file_num_lines(FILE* f) {
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

int get_max(int* vector, int num_elements) {
    int max = vector[0];
    for (int i = 1; i < num_elements; i++) {
        if (vector[i] > max) {
            max = vector[i];
        }
    }
    return max;
}

int main(int argc, char** argv) {
    int num, i, num_integers;
    char fname[100] = "entrada.txt";
    FILE* file = fopen(fname, "r");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file %s\n", fname);
        return 1;
    }
    int num_lines = file_num_lines(file);
    int* integers = malloc(sizeof(int) * num_lines);
    i = 0;
    while (fscanf(file, "%d", &num) > 0) {
        integers[i] = num;
        printf("%d\n", integers[i]);
        i++;
    }
    num_integers = i;
    printf("%d %d\n", num_integers, num_lines);
    int max_number = get_max(integers, num_integers);

    fclose(file);
    free(integers);
    return 0;
}
