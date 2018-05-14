#include "mpi.h"
#include "Collector.h"
#include "Data.h"
#include <iostream>

using namespace std;

int min(int **m, int size) {
	int res = m[0][0];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (m[i][j] < res)
				res = m[i][j];

	return res;
}

void collect(int *multipliers, int multipliersNum, int rank, int size) {
	int **res = new int*[size];

	for (int i(0); i < size; i++)
		res[i] = new int[size];

	for (int i = 0; i < multipliersNum; i++) {
		int *headers = new int[2];
		MPI_Recv(headers, 2, MPI_INT, multipliers[i], 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		int *data = new int[headers[0] * size];

		MPI_Recv(data, size * headers[0], MPI_INT, multipliers[i], 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		for (int j = headers[1]; j < headers[1] + headers[0]; j++) {
			for (int k = 0; k < size; k++) {
				res[j][k] = data[size * (j - headers[1]) + k];
			}
		}
	}

	cout << "q = MIN(MG * ML)\nq = " << min(res, size) << endl;
}
