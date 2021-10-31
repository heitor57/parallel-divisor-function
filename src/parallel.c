#include "dfpack.h"
#include "utils.h"
#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  if (world_rank == 0) {
    int max_number, num_integers;
    int *integers;

    integers = initial_setup(argc, argv, &max_number, &num_integers);

    clock_t begin = clock();

    int *integers_num_divisors = NULL;
    integers_num_divisors =
        dfpack_serial_df(integers, max_number, num_integers);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time spend with computation: %f\n", time_spent);

    write_result(argv[2], integers_num_divisors, num_integers);
    free(integers_num_divisors);
    free(integers);
  }

  MPI_Finalize();
  return 0;
}
