#include <iostream>
#include <utility>
#include "eigenpy/eigenpy.hpp"

Eigen::VectorXd jacobi(Eigen::MatrixXd Q, int N);
Eigen::MatrixXd jacobiRange(Eigen::VectorXi xN, Eigen::VectorXd xdq, int k);

BOOST_PYTHON_MODULE(jacobi) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("jacobi", jacobi);
  bp::def("jacobiRange", jacobiRange);
}