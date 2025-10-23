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

    // The first column of the result matrix contains energies, the rest are wavefunctions

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