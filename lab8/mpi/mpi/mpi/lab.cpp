#include "stdafx.h"
#include "mpi.h"
#include "Collector.h"
#include "Initializer.h"
#include "Multiplier.h"

int multipliersNum = 4;
int multipliers[] = {1, 2, 3, 4};
int initializer = 0;
int collector = 5;

bool checkIsMultiplier(int rank);

int main(int argc, char *argv[]) {
  int rank;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == initializer) {
    initialize(multipliers, 4, initializer, 10);
  } else if (checkIsMultiplier(rank)) {
    multiplicator(0, rank, collector, 10);
  } else if (rank == collector) {
    collect(multipliers, 4, rank, 10);
  }

  MPI_Finalize();

  return 0;
}

bool checkIsMultiplier(int rank) {
  for (int i = 0; i < multipliersNum; i++)
    if (multipliers[i] == rank)
      return true;

  return false;
}
