#include <iostream>
#include <utility>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"

using Eigen::MatrixXd;
// using Eigen::ArrayXd;
// using Eigen::VectorXd;

using namespace Eigen;

// Declarations
double f(double x, double y);

// Create meshgrid functionality for python contour plot
std::pair<MatrixXd, MatrixXd> meshgrid(const VectorXd& x, const VectorXd& y) 
{
    int nx = x.size();
    int ny = y.size();
    
    MatrixXd X(ny, nx);  // Note: rows=ny, cols=nx 
    MatrixXd Y(ny, nx);
    
    // Fill X matrix - each row is a copy of x vector
    for (int i = 0; i < ny; ++i) {
        X.row(i) = x.transpose();
    }
    
    // Fill Y matrix - each column is a copy of y vector
    for (int j = 0; j < nx; ++j) {
        Y.col(j) = y;
    }
    
    return std::make_pair(X, Y);
}

// Evaluate function over 2D grid
MatrixXd evaluateFunction2D(const MatrixXd& X, const MatrixXd& Y)
{
    MatrixXd Z(X.rows(), X.cols());
    
    for (int i = 0; i < X.rows(); ++i) {
        for (int j = 0; j < X.cols(); ++j) {
            Z(i, j) = f(X(i, j), Y(i, j));
        }
    }
    
    return Z;
}

// Return X, Y, Z as a Python tuple
boost::python::tuple createFunctionGrid(double xmin, double xmax, double ymin, double ymax, int N)
{
    VectorXd x = VectorXd::LinSpaced(N, xmin, xmax);
    VectorXd y = VectorXd::LinSpaced(N, ymin, ymax);

    MatrixXd X, Y;
    std::tie(X, Y) = meshgrid(x, y);
    MatrixXd Z = evaluateFunction2D(X, Y);

    return boost::python::make_tuple(X, Y, Z);
}

BOOST_PYTHON_MODULE(minimize) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("createFunctionGrid", createFunctionGrid);
}