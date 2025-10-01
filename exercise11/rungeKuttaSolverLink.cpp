#include <iostream>
#include <utility>
#include <iomanip>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"
using Eigen::MatrixXd;

using namespace Eigen;
using namespace std;

// Declarations

void rungeKuttaSolver(double a, double b, int N, double y0, double yp0, double* x, double* y);


MatrixXd verifyRungeKutta(double a, double b, int N, double y0, double yp0)
{
    // Create an Eigen matrix to hold the results
    MatrixXd result(N + 1, 2);

    // Create arrays to hold the results
    double* x = result.col(0).data();
    double* y = result.col(1).data();

    // Call the Runge-Kutta solver
    rungeKuttaSolver(a, b, N, y0, yp0, x, y);

    return result;
}

BOOST_PYTHON_MODULE(rungeKuttaSolver) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("verifyRungeKutta", verifyRungeKutta);
}