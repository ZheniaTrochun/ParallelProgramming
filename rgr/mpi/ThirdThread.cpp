#include "SecondThread.h"
#include "mpi.h"
#include "Data.h"

void secondThread(int size) {
  int rawMc[size*size];
  int rawMm[size*size];
  int rawMb[size*size];

  int** md = createMatrix(size);
  int* b = createVector(size);

  MPI_Recv(rawMc, size * size, MPI_INT, 1, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  MPI_Recv(rawMm, size * size, MPI_INT, 1, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  MPI_Recv(rawMb, size * size, MPI_INT, 3, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  MPI_Send(rawMc, size * size, MPI_INT, 3, 2, MPI_COMM_WORLD);
  MPI_Send(rawMm, size * size, MPI_INT, 3, 2, MPI_COMM_WORLD);

  MPI_Send(toRaw(md), size * size, MPI_INT, 1, 2, MPI_COMM_WORLD);
  MPI_Send(toRaw(md), size * size, MPI_INT, 3, 2, MPI_COMM_WORLD);

  MPI_Send(rawMb, size * size, MPI_INT, 1, 2, MPI_COMM_WORLD);
  MPI_Send(b, size, MPI_INT, 1, 2, MPI_COMM_WORLD);

  int** mb = parseRaw(rawMb, size, size);
  int** mc = parseRaw(rawMc, size, size);
  int** mm = parseRaw(rawMm, size, size);

  int** first = multiplyPart(mb, mc, size, size/2, 3*size/4 - size/2);
  int** second = multiplyPart(md, mm, size, size/2, 3*size/4 - size/2);

  int** res = new int*[3*size/4 - size/2];

  for(int i(0); i < 3*size/4 - size/2; i++) {
    res[i] = new int[size];
  }

  for(int i(0); i < 3*size/4 - size/2; i++) {
    for(int j(0); i < size; i++) {
      res[i][j] = first[i][j] + second[i][j];
    }
  }

  int rawFirstPart[size * size/2];

  MPI_Recv(rawFirstPart, size * size/2, MPI_INT, 1, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  int* concat = new int[3*size/4];
  int* rawSecondPart = toRaw(res);

  for(int i(0); i < size/2; i++) {
    concat[i] = rawFirstPart[i];
  }

  for(int i(size/2); i < 3*size/4; i++) {
    concat[i - size/2] = rawSecondPart[i];
  }

  MPI_Send(concat, size * 3*size/4), MPI_INT, 3, 2, MPI_COMM_WORLD);
}
