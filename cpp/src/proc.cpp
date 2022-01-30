/* See LICENSE file for copyright and license details. */

#include "proc.hpp"
#include "matrix.hpp"
#include <cmath>

Matrix procTanh(Matrix A) {
  Matrix B{A};
  for (unsigned i = 0; i < B.getRows(); i++) {
    for (unsigned j = 0; j < B.getCols(); j++) {
      B(i, j) = tanh(B(i, j));
    }
  }
  return B;
}

Matrix procEval(Matrix A) {
  Matrix B{A};
  for (unsigned i = 0; i < B.getRows(); i++) {
    for (unsigned j = 0; j < B.getCols(); j++) {
      B(i, j) = (double)A(i, j) * (1.0 - (double)A(i, j));
    }
  }
  return B;
}

double getError(Matrix A) {
  double errsum = 0.0;
  double terms = 0.0;
  for (unsigned i = 0; i < A.getRows(); i++) {
    for (unsigned j = 0; j < A.getCols(); j++) {
      errsum += (double)fabs(A(i, j));
      terms += 1.0;
    }
  }
  return errsum / terms;
}
