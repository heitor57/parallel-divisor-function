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
#ifndef NDEBUG
      printf("%d ON\n", rank);
#endif
  if (!rank) {
    int max_number, num_integers;
    int *integers;

    integers = initial_setup(argc, argv, &num_integers);
#ifndef NDEBUG
      printf("%d %d\n", rank, num_integers);
#endif

    MPI_Barrier(MPI_COMM_WORLD);
    clock_t begin = clock();

    int *integers_num_divisors = NULL;
    int *blocklenghts = malloc(sizeof(int) * comm_size);
    // send blocks lengths
    for (int i = 1; i < comm_size; i++) {
      blocklenghts[i] = BLOCK_SIZE(i-1, comm_size-1, num_integers);
#ifndef NDEBUG
      printf("%d %d\n", i, blocklenghts[i]);
#endif
      MPI_Send(&blocklenghts[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    // send integers
    for (int i = 1; i < comm_size; i++)
      MPI_Send(&integers[BLOCK_FLOOR(i-1, comm_size-1, num_integers)],
               BLOCK_SIZE(i-1, comm_size-1, num_integers), MPI_INT, i, 0,
               MPI_COMM_WORLD);

    integers_num_divisors = malloc(sizeof(int) * num_integers);

    MPI_Status status;
    // receive results
    for (int i = 1; i < comm_size; i++){
#ifndef NDEBUG
      printf("%d waiting %d\n", rank, i);
#endif
      MPI_Recv(&integers_num_divisors[BLOCK_FLOOR(i-1, comm_size-1, num_integers)],
               BLOCK_SIZE(i-1, comm_size-1, num_integers), MPI_INT, i, 0,
               MPI_COMM_WORLD, &status);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time spend with computation: %f\n", time_spent);
    // write result in output file
    write_result(argv[2], integers_num_divisors, num_integers);
    free(integers_num_divisors);
    free(integers);
    free(blocklenghts);
  } else {
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Status status;
    int num_integers;
#ifndef NDEBUG
      printf("%d PASSED FIRST BARRIER\n", rank);
#endif
    // receive block length
    MPI_Recv(&num_integers, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
#ifndef NDEBUG
      printf("%d %d\n", rank, num_integers);
#endif
    int *integers = malloc(sizeof(int) * num_integers);
    MPI_Barrier(MPI_COMM_WORLD);
    // receive integers
    MPI_Recv(&integers[0], num_integers, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
#ifndef NDEBUG
      printf("%d Received integers\n", rank);
      printf("%d Received integers with %d number\n", rank,integers[0]);
      printf("%d Received integers with %d max number\n", rank,get_max(integers, num_integers));
#endif
    int *integers_num_divisors = dfpack_serial_df(
        integers, get_max(integers, num_integers), num_integers);


    MPI_Send(&integers_num_divisors[0], num_integers, MPI_INT, 0, 0,
             MPI_COMM_WORLD);

#ifndef NDEBUG
      printf("%d finished, just waiting\n", rank);
#endif
    MPI_Barrier(MPI_COMM_WORLD);
    free(integers);
    free(integers_num_divisors);
  }

  MPI_Finalize();
  return 0;
}
