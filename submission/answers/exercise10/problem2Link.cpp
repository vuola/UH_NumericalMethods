#include <iostream>
#include <utility>
#include <iomanip>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"

using namespace Eigen;
using namespace std;

// Declarations

double gaussrng(double p);
double exp_dist_inv(double p);
double lorentz_dist_inv(double p);
int multipleAverages(int N, int K, double(*rng)(double), double* averages);
void create_histogram(const double* data, int data_size, int M, double *x, double *p);

/**
 * @file problem2Link.cpp
 * @brief Test the central limit theorem by generating random number averages
 * @brief with three different distributions
 * @param The number of samples K in one averaging
 * @return An M x 6 matrix of histograms. The columns in increasing order are: 
 * @return uniform x and p, exponential x and p, and Lorentz x and p.
*/
Eigen::MatrixXd verifyclt(int K) {
  const int N = 10000;  // Number of experiments i.e. averages
  const int M = 100;    // Number of bins for the histogram
  double data[N];
  Matrix<double, M, 6> results; // Col-major by default

  // Uniform distribution
  multipleAverages(N, K, gaussrng, data);
  create_histogram(data, N, M, results.col(0).data(), results.col(1).data());

  // Exponential distribution
  multipleAverages(N, K, exp_dist_inv, data);
  create_histogram(data, N, M, results.col(2).data(), results.col(3).data());

  // Lorentz distribution
  multipleAverages(N, K, lorentz_dist_inv, data);
  create_histogram(data, N, M, results.col(4).data(), results.col(5).data());

  return results;
}

BOOST_PYTHON_MODULE(verifyclt) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("verifyclt", verifyclt);
}