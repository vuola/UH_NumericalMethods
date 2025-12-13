#include <iostream>
#include <utility>
#include "eigenpy/eigenpy.hpp"

using Eigen::MatrixXd;
using Eigen::VectorXd;

Eigen::MatrixXd frange(VectorXd mu, double x_left, double x_right, int N);
Eigen::MatrixXd bifurcation(double x0, double mu_left, double mu_right, int N);

BOOST_PYTHON_MODULE(bifurcation) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("frange", frange);
  bp::def("bifurcation", bifurcation);
}