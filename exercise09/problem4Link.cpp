#include <iostream>
#include <utility>
#include <iomanip>
#include <vector>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"

using namespace Eigen;
using namespace std;

// Declarations
int multipleAverages(int N, int M, std::vector<double>& averages, std::vector<double>& squared_averages);

/**
 * @file problem2Link.cpp
 * @brief Function to test the quality of a random number generator
 * @brief Creates four different datasets of length M. The first two datasets use N = 1000. The second two 
 * @brief datasets use N = 10^6. Odd datasets are averaging random numbers. Even datasets are averaging 
 * @brief squares of random numbers. Place the datasets in rows of a 4 by M matrix.
*/
MatrixXd verifyRNG() {
    const int M = 100;  // Number of experiments
    MatrixXd results(4, M);

    vector<double> averages, squared_averages;

    // First two datasets (N = 1000)
    multipleAverages(1000, M, averages, squared_averages);
    results.row(0) = Map<VectorXd>(averages.data(), averages.size());
    results.row(1) = Map<VectorXd>(squared_averages.data(), squared_averages.size());

    // Last two datasets (N = 10^6)
    averages.clear();
    squared_averages.clear();
    multipleAverages(1000000, M, averages, squared_averages);
    results.row(2) = Map<VectorXd>(averages.data(), averages.size());
    results.row(3) = Map<VectorXd>(squared_averages.data(), squared_averages.size());

    return results;
}

BOOST_PYTHON_MODULE(problem4) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("verifyRNG", verifyRNG);
}