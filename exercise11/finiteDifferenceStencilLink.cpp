#include <iostream>
#include <utility>
#include <iomanip>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"
using Eigen::MatrixXd;

using namespace Eigen;
using namespace std;

// Declarations

pair<VectorXd, MatrixXd> solveEigenproblem(int N, double h);

MatrixXd finiteDifference(int N, double h)
{
    auto [energies, wavefunctions] = solveEigenproblem(N, h);

    // Create arrays to hold the results
    // double* x = wavefunctions.col(0).data();
    // double* y = wavefunctions.col(1).data();

    MatrixXd result(N, N+1);
    result.col(0) = energies;
    for (int i = 0; i < N; ++i) {
        result.col(i+1) = wavefunctions.col(i);
    }

    return result;
}

BOOST_PYTHON_MODULE(fds) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("finiteDifference", finiteDifference);
}