/* See LICENSE file for copyright and license details. */

#ifndef FRANKNET_RAND_HPP_
#define FRANKNET_RAND_HPP_

#include <random>

class Random {
private:
  std::mt19937 rng;

public:
  Random();
  virtual ~Random();
  int rInt(int, int);
  double rDouble(double, double);
};

#endif // FRANKNET_RAND_HPP_
