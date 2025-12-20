#include <iostream>
#include <utility>
#include "eigenpy/eigenpy.hpp"

using Eigen::MatrixXd;
using Eigen::VectorXd;

Eigen::MatrixXd cubicspline(int n, VectorXd boundary);

BOOST_PYTHON_MODULE(cubicspline) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("cubicspline", cubicspline);
}