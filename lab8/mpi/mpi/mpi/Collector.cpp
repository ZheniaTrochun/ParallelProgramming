#include "stdafx.h"
#include "mpi.h"
#include "Collector.h"
#include "DataBlock.h"
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
	int last = 0;

	int **res = new int*[size];
	for (int i(0); i < size; i++)
		res[i] = new int[size];

	char *tmp;
	char **headersTmp = new char*[multipliersNum];
	MultResponse **resps = new MultResponse*[multipliersNum];

	int *data;

	for (int i = 0; i < multipliersNum; i++) {
		MPI_Recv(&headersTmp[i], sizeof(struct MultResponse), MPI_CHAR, multipliers[i], DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		resps[i] = (struct MultResponse *) headersTmp[i];

		MPI_Recv(&data, size * resps[i]->rowNumber, MPI_INT, multipliers[i], DEFAULT_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
		for (int j = last; j < last + resps[i]->rowNumber; j++) {
			for (int k = 0; k < size; k++) {
				res[j][k] = data[size * (j - last) + k];
			}
		}

		last += resps[i]->rowNumber;
	}

	cout << "q = MIN(MG * ML)\nq = " << min(res, size);
}