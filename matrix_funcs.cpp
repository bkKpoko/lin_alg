#include "matrix_funcs.h"
#include <cstdio>

void gauss_jordan(Nmatrix<double> &a, Nmatrix<double> &b) {
  int i, icol, irow, j, k, l, ll, n = a.nrows(), m = b.ncols();
  double big, dum, pivinv;
  Nvector<int> indxc(n), indxr(n), ipiv(n, 0);
  for (i = 0; i < n; i++) {
    big = 0.0;
    for (j = 0; j < n; j++)
      if (ipiv[j] != 1)
        for (k = 0; k < n; k++) {
          if (ipiv[k] == 0) {
            if (std::abs(a[j][k]) >= big) {
              big = std::abs(a[j][k]);
              irow = j;
              icol = k;
            }
          }
        }
    ++(ipiv[icol]);
    if (irow != icol) {
      for (l = 0; l < n; l++)
        SWAP(a[irow][l], a[icol][l]);
      for (l = 0; l < m; l++)
        SWAP(b[irow][l], b[icol][l]);
    }
    puts("after swap");
    print(a, b);
    printf("pivinv = %g\n", pivinv);
    indxr[i] = irow;
    indxc[i] = icol;
    if (a[icol][icol] == 0.0)
      throw std::runtime_error("gaussj: Singular Matrix");
    pivinv = 1.0 / a[icol][icol];
    printf("a[%i, %i] = %g\n", icol, icol, a[icol][icol]);
    printf("pivinv = %g\n", pivinv);
    a[icol][icol] = 1.0;
    print(a, b);
    for (l = 0; l < n; l++)
      a[icol][l] *= pivinv;
    for (l = 0; l < m; l++)
      b[icol][l] *= pivinv;
    puts("*= pivinv");
    print(a, b);
    for (ll = 0; ll < n; ll++)
      if (ll != icol) {
        dum = a[ll][icol];
        a[ll][icol] = 0.0;
        for (l = 0; l < n; l++)
          a[ll][l] -= a[icol][l] * dum;
        for (l = 0; l < m; l++)
          b[ll][l] -= b[icol][l] * dum;
      }
    print(a, b);
  }
  for (l = n - 1; l >= 0; l--) {
    if (indxr[l] != indxc[l])
      for (k = 0; k < n; k++)
        SWAP(a[k][indxr[l]], a[k][indxc[l]]);
    print(a, b);
  }
}

void gaussj(Nmatrix<double> &a) {
  Nmatrix<double> b(a.nrows(), 0);
  gauss_jordan(a, b);
}
