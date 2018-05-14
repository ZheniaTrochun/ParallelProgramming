#include "Data.h"
#include "Initializer.h"
#include "mpi.h"

void initialize(int *multipliers, int multipliersNum, int rank, int size) {
	int **mg = createMatrix(size);
	int **ml = createMatrix(size);

	int *rawMg = toRaw(mg, size, size);
	int *rawMl = toRaw(ml, size, size);

	for (int i = 0; i < multipliersNum; i++) {
		int data[] = { i * size / multipliersNum, (i + 1) * size / multipliersNum };

		MPI_Send(data, 2, MPI_INT, multipliers[i], 1, MPI_COMM_WORLD);
		MPI_Send(rawMg, size * size, MPI_INT, multipliers[i], 2, MPI_COMM_WORLD);
		MPI_Send(rawMl, size * size, MPI_INT, multipliers[i], 3, MPI_COMM_WORLD);
	}
}
