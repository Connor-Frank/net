/* See LICENSE file for copyright and license details. */

#include "rand.hpp"
#include "util.hpp"
#include <cmath>
#include <random>

Random::Random() { rng.seed(1); }

Random::~Random() {}

int Random::rInt(int min, int max) {
  if (min >= max) {
    die("minimum value needs to be less than maximum value.");
  }
  std::uniform_int_distribution<int> udist(min, max);

  return udist(rng);
}

double Random::rDouble(double min, double max) {
  if (min >= max) {
    die("minimum value needs to be less than maximum value.");
  }
  std::uniform_real_distribution<double> dist(min, max);

  return dist(rng);
}
