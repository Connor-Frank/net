/* See LICENSE file for copyright and license details. */

#ifndef FRANKNET_MATRIX_HPP_
#define FRANKNET_MATRIX_HPP_

#include <vector>
#include <tuple>
#include "rand.hpp"

class Matrix {
private:
    std::vector<std::vector<double> > m_matrix;
    unsigned rows, cols;

public:
    Matrix(unsigned, unsigned, double, double, Random);
    Matrix(unsigned, unsigned, double);
    Matrix(const Matrix &);
    virtual ~Matrix();

    double& operator()(const unsigned &, const unsigned &);

    void operator=(Matrix);

    // Matrix math
    Matrix operator+(Matrix);
    Matrix operator-(Matrix);
    Matrix operator*(Matrix);
    Matrix transpose(void);
    Matrix dot(Matrix);

    // Scalar math
    Matrix operator+(double);
    Matrix operator-(double);
    Matrix operator*(double);
    Matrix operator/(double);

    unsigned getRows() const;
    unsigned getCols() const;
    void print() const;
};

#endif // FRANKNET_MATRIX_HPP_
