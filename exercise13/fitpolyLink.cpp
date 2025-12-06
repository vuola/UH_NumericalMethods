#include <iostream>
#include <utility>
#include <iomanip>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"

using namespace Eigen;
using namespace std;


// Define which fitting function to use: 'a' for fitpoly_primitive, 'c' for fitpoly
#define FITFUNC 'a'


// Declarations
double* fitpoly(int p, int n);
double* fitpoly_primitive(int p, int n);
void evalpoly(double* c, int p, int m, double* x_data, double* y_data);

/**
 * @file fitpolyLink.cpp
 * @brief Finds parameters of a primitive polynomial of degree p-1 fitted to f(x)=sin(pi*x), x in [-2, 2] using fitpoly. Model parameters are printed to standard output. Evaluates fitted polynomial at n points and returns a m x 3 matrix of [x, f(x), fitted_fx]
 * @param p number of parameters
 * @param n number of data points for fitting
 * @param m number of evaluation points
 * @return A m x 3 matrix. The first column contains the x values, the second column the f(x) values, and the third column the fitted values.
*/

Eigen::MatrixXd evaluateFitpoly(int p, int n, int m) {
    // Allocate output matrix
    Eigen::MatrixXd result(m, 3);

    // Fit polynomial to data
    #if FITFUNC == 'c'
    double* c = fitpoly(p, n);
    #elif FITFUNC == 'a'
    double* c = fitpoly_primitive(p, n);
    #endif

    // Evaluate fitted polynomial at m points. Use pointers to output matrix columns to store results
    double* x_data = result.col(0).data();
    double* y_data = result.col(2).data();

    evalpoly(c, p, m, x_data, y_data);
 
    // Fill in the second column with actual f(x) values
    double* f_data = result.col(1).data();
    for (int i = 0; i < m; ++i) {
        f_data[i] = sin(M_PI * x_data[i]);
    }
    
    return result;
} 


/**
 * @file fitpolyLink.cpp
 * @brief Evaluates f(x) = sin(pi*x) at m points
 * @param m number of x points
 * @return A (m x 2) matrix. The first column contains x 
 * values, and the second column f(x) values.
 * */
Eigen::MatrixXd evaluateF(int m) {
    Eigen::MatrixXd M(m, 2);
    VectorXd x = VectorXd::LinSpaced(m, -2.0, 2.0);

    for (int i = 0; i < m; ++i) {
        M(i, 0) = x(i);
        M(i, 1) = sin(M_PI * x(i));
      }
    return M;
}


BOOST_PYTHON_MODULE(fitpoly) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("evaluateFitpoly", evaluateFitpoly);
  bp::def("evaluateF", evaluateF);
}