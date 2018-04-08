#include "stdafx.h"
#include "Initializer.h"
#include "mpi.h"

void initialize(int *multipliers, int multipliersNum, int rank, int size) {
	int **mg = new int*[size];
	int **ml = new int*[size];

	for (int i = 0; i < size; i++) {
		mg[i] = new int[size];
		ml[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mg[i][j] = 1;
			ml[i][j] = 1;
		}
	}

	int *rawMg = new int[size * size];
	int *rawMl = new int[size * size];

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			rawMg[i * size + j] = mg[i][j];
			rawMl[i * size + j] = ml[i][j];
		}
	}

	for (int i = 0; i < multipliersNum; i++) {
		int data[] = { i * size / multipliersNum, (i + 1) * size / multipliersNum };

		MPI_Send(data, 2, MPI_INT, multipliers[i], 1, MPI_COMM_WORLD);
		MPI_Send(rawMg, size * size, MPI_INT, multipliers[i], 2, MPI_COMM_WORLD);
		MPI_Send(rawMl, size * size, MPI_INT, multipliers[i], 3, MPI_COMM_WORLD);
	}
}
