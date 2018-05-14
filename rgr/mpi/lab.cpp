#include "mpi.h"
#include "Collector.h"
#include "Initializer.h"
#include "Multiplier.h"

int size = 100;

int main(int argc, char *argv[]) {
  int rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    firstThread(size);
  } else if (rank == 1) {
    secondThread(size);
  } else if (rank == 2) {
    thirdThread(size);
  } else if (rank == 3) {
    forthThread(size);
  }

  MPI_Finalize();

  return 0;
}
