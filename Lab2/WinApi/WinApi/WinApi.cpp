// WinApi.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "Data.h"

using namespace std;

int main()
{
	int n;

	cout << "Enter matrix size: ";
	cin >> n;

	int **mf, **ml, **mk;

	mf = createMatrix(n);
	mk = createMatrix(n);
	ml = createMatrix(n);

	mf = calculateFunc(mf, mk, ml, n);

	system("pause");
    return 0;
}

