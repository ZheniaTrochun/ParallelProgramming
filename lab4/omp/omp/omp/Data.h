#pragma once
#include <omp.h>
#include <iostream>

const int NUM_THREADS = 4;

using namespace std;

int** generateMatrix(int n);
int** multiplyMatrixes(int **a, int **b, int n);
int** multiplyMatrix(int **a, int b, int n);
int   min(int **a, int n);
void  printMatrix(int **a, int n);