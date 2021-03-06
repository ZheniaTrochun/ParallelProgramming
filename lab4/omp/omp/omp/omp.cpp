// omp.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Data.h"


int main()
{
	int n = 10;
	
	int **MG = generateMatrix(n);
	int **MK = generateMatrix(n);

	int m;
	int **tmp = new int*[n];

	for (int i(0); i < n; i++)
		tmp[i] = new int[n];

//	#pragma omp single nowait
	#pragma omp sections
	{
//		#pragma omp task
		#pragma omp section
			m = min(MG, n);

//		#pragma omp task
		#pragma omp section
			tmp = multiplyMatrixes(MG, MK, n);
	}
	
//	#pragma omp taskwait
	#pragma omp barrier
		printMatrix(multiplyMatrix(tmp, m, n), n);

    return 0;
}

