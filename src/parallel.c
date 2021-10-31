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
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  if (!rank) {
    int max_number, num_integers;
    int *integers;

    integers = initial_setup(argc, argv, &num_integers);

    MPI_Barrier(MPI_COMM_WORLD);
    clock_t begin = clock();

    int *integers_num_divisors = NULL;
    int *blocklenghts = malloc(sizeof(int) * comm_size-1);
    for (int i = 1; i < comm_size; i++) {
      blocklenghts[i] = BLOCK_SIZE(i, comm_size-1, num_integers);
#ifdef DEBUG
      printf("%d %d\n", i, blocklenghts[i]);
#endif
      MPI_Send(&blocklenghts[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    for (int i = 1; i < comm_size; i++)
      MPI_Send(&integers[BLOCK_FLOOR(i, comm_size-1, num_integers)],
               BLOCK_SIZE(i, comm_size-1, num_integers), MPI_INT, i, 0,
               MPI_COMM_WORLD);

    integers_num_divisors = malloc(sizeof(int) * num_integers);

    MPI_Status status;
    for (int i = 1; i < comm_size; i++)
      MPI_Recv(&integers_num_divisors[BLOCK_FLOOR(i, comm_size-1, num_integers)],
               BLOCK_SIZE(i, comm_size-1, num_integers), MPI_INT, i, 0,
               MPI_COMM_WORLD, &status);

    MPI_Barrier(MPI_COMM_WORLD);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time spend with computation: %f\n", time_spent);

    write_result(argv[2], integers_num_divisors, num_integers);
    free(integers_num_divisors);
    free(integers);
    free(blocklenghts);
  } else {
#ifdef DEBUG
      printf("%d ON\n", i);
#endif
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Status status;
    int num_integers;
#ifdef DEBUG
      printf("%d PASSED FIRST BARRIER\n", i);
#endif
    MPI_Recv(&num_integers, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
#ifdef DEBUG
      printf("%d %d\n", i, num_integers);
#endif
    int *integers = malloc(sizeof(int) * num_integers);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Recv(&integers, num_integers, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    int *integers_num_divisors = dfpack_serial_df(
        integers, get_max(integers, num_integers), num_integers);

    MPI_Send(&integers_num_divisors, num_integers, MPI_INT, 0, 0,
             MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}
