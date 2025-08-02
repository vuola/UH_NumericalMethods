#include <iostream>
#include <utility>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"
 
// using Eigen::MatrixXd;
// using Eigen::ArrayXd;
using Eigen::VectorXd;

using namespace Eigen;

double f(double x);

VectorXd goldenRange(double first, double last, int N)
{
    VectorXd Xpoints = VectorXd::LinSpaced(N, first, last);
    VectorXd Fpoints(N);
    for (int i=0; i<N; ++i) {
        Fpoints(i) = f(Xpoints(i));
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
