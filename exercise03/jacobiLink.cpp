#include <iostream>
#include <utility>
#include "eigenpy/eigenpy.hpp"

Eigen::VectorXd jacobi(Eigen::MatrixXd Q, int N);

BOOST_PYTHON_MODULE(jacobi) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("jacobi", jacobi);
}