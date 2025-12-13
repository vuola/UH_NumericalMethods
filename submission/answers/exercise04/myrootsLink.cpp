#include <iostream>
#include <utility>
#include "eigenpy/eigenpy.hpp"

using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::VectorXcd;

VectorXcd myroots(int N, VectorXd a);
VectorXcd evalP(VectorXd a, VectorXcd X);

BOOST_PYTHON_MODULE(myroots) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("myroots", myroots);
  bp::def("evalP", evalP);
}