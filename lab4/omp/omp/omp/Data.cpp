#include "stdafx.h"
#include "Data.h"

int** generateMatrix(int n) {
	int** matrix = new int*[n];

	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = 1;

	return matrix;
}

int** multiplyMatrix(int **a, int num, int n) {
	int** matrix = new int*[n];

	for (int i = 0; i < n; i++)
		matrix[i] = new int[n];

	#pragma omp parallel for num_threads(NUM_THREADS)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = a[i][j] * num;

	return matrix;
}

void  printMatrix(int **a, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << a[i][j] << "\t";

		cout << endl;
	}

	system("pause");
}

int min(int **a, int n) {
	int min = a[0][0];

	#pragma omp parallel for num_threads(NUM_THREADS)
		for (int i(0); i < n; i++)
			for (int j(0); j < n; j++)
				if (a[i][j] < min) 
					min = a[i][j];

	return min;
}

int** multiplyMatrixes(int **a, int **b, int n) {
	int** res = new int*[n];

	for (int i = 0; i < n; i++)
		res[i] = new int[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			res[i][j] = 0;

	#pragma omp parallel for num_threads(NUM_THREADS)
		for (int i = 0; i < n; i++) 
			for (int j = 0; j < n; j++) 
				for (int k = 0; k < n; k++) 
					res[i][j] += a[i][k] * b[k][j];

	return res;
}