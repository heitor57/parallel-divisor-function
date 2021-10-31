#include "dfpack.h"
#include "utils.h"
#include <mpi.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BLOCK_FLOOR(id, m, n) ((id) * (n) / (m))
#define BLOCK_CEIL(id, m, n) (BLOCK_FLOOR((id) + 1, m, n) - 1)
#define BLOCK_SIZE(id, m, n) (BLOCK_CEIL(id, m, n) - BLOCK_FLOOR(id, m, n) + 1)

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int comm_size;
  MPI_Comm_size (MPI_COMM_WORLD, &comm_size);
  if (!rank) {
    int max_number, num_integers;
    int *integers;

    integers = initial_setup(argc, argv, &max_number, &num_integers);

    MPI_Barrier(MPI_COMM_WORLD);
    clock_t begin = clock();

    int *integers_num_divisors = NULL;
    integers_num_divisors =
        dfpack_parallel_df(integers, max_number, num_integers,rank,comm_size);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time spend with computation: %f\n", time_spent);

    write_result(argv[2], integers_num_divisors, num_integers);
    free(integers_num_divisors);
    free(integers);
  }else{
      MPI_Barrier(MPI_COMM_WORLD);
      dfpack_parallel_df(NULL, -1,-1, rank,comm_size);
  }

  MPI_Finalize();
  return 0;
}
