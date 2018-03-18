#include "stdafx.h"
#include "Data.h"
#include <stdlib.h>
#include <iostream>
#include <Windows.h>

#define THREADS_NUMBER 3

using namespace std;

CRITICAL_SECTION output;
HANDLE firstPart;
HANDLE secondPart;
HANDLE matrixTrans;

int **MF;
int ** MK, **ML, **tmp;
int N;

DWORD WINAPI transposeMatrix(CONST LPVOID lpParam);
DWORD WINAPI multFirstPartMatrix(CONST LPVOID lpParam);
DWORD WINAPI multSecondPartMatrix(CONST LPVOID lpParam);


DWORD WINAPI transposeMatrix(CONST LPVOID lpParam) {
	MF = trans(MF, N);

	SetEvent(matrixTrans);

	EnterCriticalSection(&output);
	cout << "transposition done: \n";
	LeaveCriticalSection(&output);

	ExitThread(0);
}

DWORD WINAPI multFirstPartMatrix(CONST LPVOID lpParam) {
	for (int i(0); i < N / 2; i++) {
		for (int j(0); j < N; j++) {
			tmp[i][j] = 0;
			for (int k(0); k < N; k++) {
				tmp[i][j] += MK[i][k] * ML[k][j];
			}
		}
	}

	SetEvent(firstPart);

	EnterCriticalSection(&output);
	cout << "first part of multiplication done: \n";
	LeaveCriticalSection(&output);

	ExitThread(0);
}

DWORD WINAPI multSecondPartMatrix(CONST LPVOID lpParam) {
	for (int i(N/2); i < N; i++) {
		for (int j(0); j < N; j++) {
			tmp[i][j] = 0;
			for (int k(0); k < N; k++) {
				tmp[i][j] += MK[i][k] * ML[k][j];
			}
		}
	}

	SetEvent(secondPart);

	EnterCriticalSection(&output);
	cout << "second part of multiplication done: \n";
	LeaveCriticalSection(&output);

	ExitThread(0);
}

int **createMatrix(int n) {
	int **m = new int*[n];
	for (int i(0); i < n; i++) {
		m[i] = new int[n];
		for (int j(0); j < n; j++) {
			m[i][j] = 1;
		}
	}

	return m;
}

int **trans(int **m, int n) {
	int **tmp = new int*[n];
	for (int i(0); i < n; i++) {
		tmp[i] = new int[n];
	}

	for (int i(0); i < n; i++) {
		for (int j(0); j < n; j++) {
			tmp[j][i] = m[i][j];
		}
	}

	return tmp;
}

void printMatrix(int **m, int n) {
	for (int i(0); i < n; i++) {
		for (int j(0); j < n; j++) {
			cout << m[i][j] << "\t";
		}
		cout << endl;
	}
}

int **calculateFunc(int **mf, int **mk, int **ml, int n) {
	tmp = new int*[n];
	for (int i(0); i < n; i++) {
		tmp[i] = new int[n];
	}

	for (int i(0); i < n; i++) {
		for (int j(0); j < n; j++) {
			tmp[j][i] = 0;
		}
	}

	MF = mf;
	MK = mk;
	ML = ml;
	N = n;

	InitializeCriticalSectionAndSpinCount(&output, 0x00000400);
	firstPart = CreateEvent(NULL, TRUE, FALSE, TEXT("Matrix first part"));
	secondPart = CreateEvent(NULL, TRUE, FALSE, TEXT("Matrix second part"));
	matrixTrans = CreateEvent(NULL, TRUE, FALSE, TEXT("Matrix transponation"));

	HANDLE hThreads[THREADS_NUMBER];

	hThreads[0] = CreateThread(NULL, 0, &transposeMatrix, NULL, 0, NULL);
	hThreads[0] = CreateThread(NULL, 0, &multFirstPartMatrix, NULL, 0, NULL);
	hThreads[0] = CreateThread(NULL, 0, &multSecondPartMatrix, NULL, 0, NULL);

	WaitForSingleObject(transposeMatrix, INFINITE);
	WaitForSingleObject(firstPart, INFINITE);
	WaitForSingleObject(secondPart, INFINITE);

	for (int i(0); i < n; i++) {
		for (int j(0); j < n; j++) {
			MF[i][j] += tmp[i][j];
		}
	}

	EnterCriticalSection(&output);

	cout << "all operations done: \n";
	printMatrix(MF, n);

	LeaveCriticalSection(&output);


	return MF;
}