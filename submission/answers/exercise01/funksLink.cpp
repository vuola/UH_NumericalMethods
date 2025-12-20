#include <iostream>
#include <utility>
#include "eigenpy/eigenpy.hpp"

Eigen::MatrixXd funksRange(double first, double last, int N);

BOOST_PYTHON_MODULE(funks) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  /*  Eigen::MatrixXd (*funksRange)(double, double, int) = funksRange; */
  bp::def("funksRange", funksRange);
}
