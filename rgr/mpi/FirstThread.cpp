#include "FirstThread.h"
#include "mpi.h"
#include "Data.h"

void firstThread(int size) {
  int** mc = createMatrix(size);
  int** mm = createMatrix(size);

  int rawMd[size*size];
  int rawMb[size*size];
  int b[size];

  int* rawMc = toRaw(mc, size, size);
  int* rawMm = toRaw(mm, size, size);

  MPI_Send(rawMc, size * size, MPI_INT, 1, 2, MPI_COMM_WORLD);
  MPI_Send(rawMm, size * size, MPI_INT, 1, 2, MPI_COMM_WORLD);

  MPI_Recv(rawMd, size * size, MPI_INT, initializer, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  MPI_Recv(rawMb, size * size, MPI_INT, initializer, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  MPI_Recv(b, size, MPI_INT, initializer, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  int** md = parseRaw(rawMd, size, size);
  int** mb = parseRaw(rawMb, size, size);

  int** first = multiplyPart(mb, mc, size, 0, size/4);
  int** second = multiplyPart(md, mm, size, 0, size/4);

  int** res = new int*[size/4];

  for(int i(0); i < size/4; i++) {
    res[i] = new int[size];
  }

  for(int i(0); i < size/4; i++) {
    for(int j(0); i < size; i++) {
      res[i][j] = first[i][j] + second[i][j];
    }
  }

  MPI_Send(toRaw(res), size * size/4, MPI_INT, 1, 2, MPI_COMM_WORLD);
}
