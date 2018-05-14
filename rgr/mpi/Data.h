
int** createMatrix(int size);
int* createVector(int size);

int** parseRaw(int *raw, int num, int size);
int* toRaw(int** m, int num, int size);

int** multiplyPart(int** f, int** s, int size, int start, int num);
