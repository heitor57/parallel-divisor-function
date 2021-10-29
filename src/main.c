#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#include "df_utils.h"


int main(int argc, char **argv) {
  int max_number,num_integers;
  int *integers;
  integers =initial_setup(argc,argv,&max_number,&num_integers);
  int * integers_num_divisors= df_utils_serial_df(integers, max_number, num_integers);
  write_result(argv[2], integers_num_divisors, num_integers);
  free(integers_num_divisors);
  free(integers);
  free(integers_num_divisors);
  return 0;
}
