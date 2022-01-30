/* See LICENSE file for copyright and license details. */

#include "csv.hpp"
#include "matrix.hpp"
#include "proc.hpp"
#include "rand.hpp"
#include "util.hpp"
#include <iostream>
#include <vector>

int main(int argc, char **argv) {
  if (argc != 2) {
    die("usage: %s 'FILE_NAME'", argv[0]);
  }
  std::string filename = argv[1];
  std::cout << "file path: " << filename << '\n';
  Parser parser{filename};
  auto data = parser.data;

  unsigned input_size = 4;
  unsigned num_inputs = data.size() / input_size;
  unsigned rows = input_size;
  unsigned cols = data[0].size();

  unsigned curr = 0;
  std::vector<Matrix> inputs;
  for (unsigned in = 0; in < num_inputs; in++) {
    Matrix line{rows, cols, 0};
    for (unsigned i = 0; i < rows; i++) {
      for (unsigned j = 0; j < cols; j++) {
        line(i, j) = data[curr][j];
      }
      curr++;
    }

    inputs.push_back(line);
  }

  std::vector<Matrix> results;
  for (auto &input : inputs) {
    Matrix line{input_size, 1, 0};
    for (unsigned i = 0; i < input_size; i++) {
      line(i, 0) = input(i, 0);
    }
    results.push_back(line);
  }

  const unsigned steps = 1000000;
  const unsigned p_int = steps / 10;

  Random rand;
  Matrix hid0{cols, rows, -0.5, 0.5, rand};
  Matrix hid1{rows, 1, -0.5, 0.5, rand};

  for (unsigned i = 0; i <= steps; i++) {
    int type = (i % 2 == 0) ? 0 : 1;
    Matrix l0{inputs[type]};
    Matrix l1 = procTanh(l0.dot(hid0));
    Matrix l2 = procTanh(l1.dot(hid1));
    Matrix l2_error = results[type] - l2;

    if (i % p_int == 0) {
      std::cout << "error after i = " << i << ": " << getError(l2_error)
                << '\n';
    } else {
      std::cout << "error after i = " << i << ": " << getError(l2_error)
                << '\r';
    }

    Matrix l2_delta = l2_error * procEval(l2);
    Matrix l1_error = l2_delta.dot(hid1.transpose());
    Matrix l1_delta = l1_error * procEval(l1);

    hid1 = hid1 + (l1.transpose().dot(l2_delta));
    hid0 = hid0 + (l0.transpose().dot(l1_delta));
  }

  std::cout << '\n' << "output after training:" << '\n';
  if (1 == 1) {
    Matrix l0{inputs[0]};
    Matrix l1 = procTanh(l0.dot(hid0));
    Matrix l2 = procTanh(l1.dot(hid1));
    l0.print();
    l2.print();
  }

  Matrix l0{inputs[1]};
  Matrix l1 = procTanh(l0.dot(hid0));
  Matrix l2 = procTanh(l1.dot(hid1));
  l0.print();
  l2.print();

  return 0;
}
