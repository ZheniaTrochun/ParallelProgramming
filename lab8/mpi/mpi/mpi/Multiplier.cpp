#include "stdafx.h"
#include "Multiplier.h"
#include "mpi.h"
#include "DataBlock.h"

void multiplicator(int initializer, int rank, int collector, int size) {
	int *metadata;
	int *mgRaw;
	int *mlRaw;

	MPI_Recv(&metadata, 2, MPI_INT, initializer, DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&mgRaw, size * size, MPI_INT, initializer, DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(&mlRaw, size * size, MPI_INT, initializer, DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	int **mg = new int*[size];
	int **ml = new int*[size];

	int num = metadata[1] - metadata[0];

	int **res = new int*[num];

	for (int i(0); i < num; i++) {
		res[i] = new int[size];
	}

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < size; j++) {
			res[i][j] = 0;
		}
	}

	for (int i(0); i < size; i++) {
		mg[i] = new int[size];
		ml[i] = new int[size];
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mg[i][j] = mgRaw[i * size + j];
			ml[i][j] = mlRaw[i * size + j];
		}
	}

	for (int i = metadata[0]; i < metadata[1]; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				res[i - num][j] += mg[i][k] * ml[k][j];
			}
		}
	}

	MultResponse resp;
	resp.rowNumber = num;
	resp.rowSize = size;
	resp.number = metadata[0];

	int *resRaw = new int[num * size];

	for (int i = 0; i < num; i++) {
		for (int j = 0; j < size; j++) {
			resRaw[i * size + j] = res[i][j];
		}
	}

	MPI_Send(&resp, sizeof(resp), MPI_CHAR, collector, DEFAULT_TAG, MPI_COMM_WORLD);
	MPI_Send(&resRaw, num * size, MPI_INT, collector, DEFAULT_TAG, MPI_COMM_WORLD);
}