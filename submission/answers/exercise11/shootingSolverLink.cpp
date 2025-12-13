#include <iostream>
#include <utility>
#include <iomanip>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"
using Eigen::MatrixXd;

using namespace Eigen;
using namespace std;

// Declarations

void shootingSolver(double a, double b, int N, double y0, double y1, double* x, double* y);

MatrixXd shootingRange(double a, double b, int N, double y0, double y1)
{
    // Create an Eigen matrix to hold the results
    MatrixXd result(N + 1, 2);

    // Create arrays to hold the results
    double* x = result.col(0).data();
    double* y = result.col(1).data();

    // Call the shooting solver
    shootingSolver(a, b, N, y0, y1, x, y);

    return result;
}

BOOST_PYTHON_MODULE(shooting) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("shootingRange", shootingRange);
}