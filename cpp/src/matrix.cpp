/* See LICENSE file for copyright and license details. */

#include "matrix.hpp"
#include "rand.hpp"
#include "util.hpp"
//#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

// Random Matrix
Matrix::Matrix(unsigned n_rows, unsigned n_cols, double min, double max,
               Random rand) {
  rows = n_rows;
  cols = n_cols;
  for (unsigned i = 0; i < rows; i++) {
    std::vector<double> tmp;
    for (unsigned j = 0; j < cols; j++) {
      tmp.push_back(rand.rDouble(min, max));
    }
    m_matrix.push_back(tmp);
  }
}

// Filled Matrix
Matrix::Matrix(unsigned n_rows, unsigned n_cols, double initial) {
  rows = n_rows;
  cols = n_cols;
  m_matrix.resize(n_rows);
  for (unsigned i = 0; i < m_matrix.size(); i++) {
    m_matrix[i].resize(n_cols, initial);
  }
}

// Copy Matrix
Matrix::Matrix(const Matrix &B) {
  this->cols = B.cols;
  this->rows = B.rows;
  this->m_matrix = B.m_matrix;
}

Matrix::~Matrix() {}

double &Matrix::operator()(const unsigned &row, const unsigned &col) {
  return this->m_matrix[row][col];
}

void Matrix::operator=(Matrix B) { m_matrix = B.m_matrix; }

Matrix Matrix::operator+(Matrix B) {
  Matrix sum{rows, cols, 0.0};
  for (unsigned i = 0; i < rows; i++) {
    for (unsigned j = 0; j < cols; j++) {
      sum(i, j) = this->m_matrix[i][j] + B(i, j);
    }
  }
  return sum;
}

Matrix Matrix::operator-(Matrix B) {
  Matrix diff{rows, cols, 0.0};
  for (unsigned i = 0; i < rows; i++) {
    for (unsigned j = 0; j < cols; j++) {
      diff(i, j) = this->m_matrix[i][j] - B(i, j);
    }
  }
  return diff;
}

Matrix Matrix::operator*(Matrix B) {
  Matrix multip{rows, B.cols, 0.0};
  for (unsigned i = 0; i < rows; i++) {
    for (unsigned j = 0; j < cols; j++) {
      multip(i, j) = this->m_matrix[i][j] * B(i, j);
    }
  }
  return multip;
}

Matrix Matrix::transpose() {
  Matrix Transpose{cols, rows, 0.0};
  for (unsigned i = 0; i < cols; i++) {
    for (unsigned j = 0; j < rows; j++) {
      Transpose(i, j) = this->m_matrix[j][i];
    }
  }
  return Transpose;
}

Matrix Matrix::dot(Matrix B) {
  Matrix multip{rows, B.cols, 0.0};
  if (cols == B.rows) {
    double temp = 0.0;
    for (unsigned i = 0; i < rows; i++) {
      for (unsigned j = 0; j < B.cols; j++) {
        temp = 0.0;
        for (unsigned k = 0; k < cols; k++) {
          temp += m_matrix[i][k] * B(k, j);
        }
        multip(i, j) = temp;
      }
    }
  } else {
    die("error: %ux%u with %ux%u", rows, cols, B.rows, B.cols);
  }
  return multip;
}

Matrix Matrix::operator+(double scalar) {
  Matrix result{rows, cols, 0.0};
  for (unsigned i = 0; i < rows; i++) {
    for (unsigned j = 0; j < cols; j++) {
      result(i, j) = this->m_matrix[i][j] + scalar;
    }
  }
  return result;
}

Matrix Matrix::operator-(double scalar) {
  Matrix result{rows, cols, 0.0};
  for (unsigned i = 0; i < rows; i++) {
    for (unsigned j = 0; j < cols; j++) {
      result(i, j) = this->m_matrix[i][j] - scalar;
    }
  }
  return result;
}

Matrix Matrix::operator*(double scalar) {
  Matrix result{rows, cols, 0.0};
  for (unsigned i = 0; i < rows; i++) {
    for (unsigned j = 0; j < cols; j++) {
      result(i, j) = this->m_matrix[i][j] * scalar;
    }
  }
  return result;
}

Matrix Matrix::operator/(double scalar) {
  Matrix result{rows, cols, 0.0};
  for (unsigned i = 0; i < rows; i++) {
    for (unsigned j = 0; j < cols; j++) {
      result(i, j) = this->m_matrix[i][j] / scalar;
    }
  }
  return result;
}

unsigned Matrix::getRows() const { return rows; }

unsigned Matrix::getCols() const { return cols; }

void Matrix::print() const {
  // int precision = std::numeric_limits<double>::max_digits10;
  std::cout << rows << 'x' << cols << " matrix:" << '\n';
  for (unsigned i = 0; i < rows; i++) {
    for (unsigned j = 0; j < cols; j++) {
      // std::cout << std::fixed << std::setprecision(precision) << "[" <<
      // m_matrix[i][j] << "] ";
      std::cout << "[" << m_matrix[i][j] << "] ";
    }
    std::cout << '\n';
  }
}
