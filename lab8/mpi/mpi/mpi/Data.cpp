#include "Data.h"

int** createMatrix(int size) {
  int **res = new int*[size];

	for (int i = 0; i < size; i++)
		res[i] = new int[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			res[i][j] = 1;

  return res;
}

int** parseRaw(int *raw, int num, int size) {
  int **res = new int*[num];

	for (int i = 0; i < num; i++)
		res[i] = new int[size];

  for (int i = 0; i < num; i++)
    for (int j = 0; j < size; j++)
      res[i][j] = raw[i * num + j];

  return res;
}

int* toRaw(int **m, int num, int size) {
  int *resRaw = new int[num * size];

  for (int i = 0; i < num; i++)
    for (int j = 0; j < size; j++)
      resRaw[i * size + j] = m[i][j];

  return resRaw;
}
