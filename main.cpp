#include "matrix_funcs.h"
#include "num3.h"
#include <cstdio>

int main(int argc, char *argv[]) {
  Nmatrix<double> a{{3, 2, -5}, {2, -1, 3}, {1, 2, -1}};
  Nmatrix<double> b{{-1}, {13}, {9}};
  puts("Matrix a");
  a.print();
  puts("Matrix b");
  b.print();
  puts("Extended Matrix");
  print<Nmatrix<double>>(a, b, 2);

  puts("Gauss output");
  gauss_jordan(a, b);

  puts("Matrix a");
  a.print(2);
  puts("Matrix b");
  b.print();

  return 0;
}
