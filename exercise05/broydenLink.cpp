#include <iostream>
#include <utility>
#include "eigenpy/eigenpy.hpp"

using Eigen::MatrixXd;
using Eigen::VectorXd;

Eigen::VectorXd broyden(VectorXd x_init);

BOOST_PYTHON_MODULE(broyden) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("broyden", broyden);
}