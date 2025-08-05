#include <iostream>
#include <utility>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"
using Eigen::MatrixXd;
// using Eigen::ArrayXd;
using Eigen::VectorXd;

using namespace Eigen;

double f(double x);

MatrixXd goldenRange(double first, double last, int N)
{
    VectorXd Xpoints = VectorXd::LinSpaced(N, first, last);
    MatrixXd Fpoints(2, N);
    for (int i=0; i<N; ++i) {
        Fpoints(0, i) = Xpoints(i);
        Fpoints(1, i) = f(Xpoints(i));
    }
    return Fpoints;
}

BOOST_PYTHON_MODULE(golden) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

//  bp::def("golden", golden);
  bp::def("goldenRange", goldenRange);
}
