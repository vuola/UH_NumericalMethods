#include <iostream>
#include <utility>
#include <iomanip>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"
using Eigen::MatrixXd;

using namespace Eigen;
using namespace std;

// Declarations
MatrixXd verifyLorentzDistribution(int M, int N, double min_x, double max_x);

BOOST_PYTHON_MODULE(gaussrng) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("verifyLorentzDistribution", verifyLorentzDistribution);
}