#include <iostream>
#include <utility>
#include <iomanip>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"

using namespace Eigen;
using namespace std;

// Declarations
int multipleAverages(int N, int M, double* averages, double* squared_averages);

/**
 * @file problem2Link.cpp
 * @brief Function to test the quality of a random number generator, different use of memory
 * @brief Creates four different datasets of length M. The first two datasets use N = 1000. The second two 
 * @brief datasets use N = 10^6. Odd datasets are averaging random numbers. Even datasets are averaging 
 * @brief squares of random numbers.
*/
Eigen::MatrixXd verifyRNG() {
  const int M = 100;  // Number of experiments
  Matrix<double, M, 4> results; // Col-major by default

  // Directly use pointers to the underlying data for each row
  multipleAverages(1000, M, results.col(0).data(), results.col(1).data());
  multipleAverages(1000000, M, results.col(2).data(), results.col(3).data());

  return results;
}

BOOST_PYTHON_MODULE(moment) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("verifyRNG", verifyRNG);
}