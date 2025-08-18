#include <iostream>
#include <utility>
#include <iomanip>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"

using namespace Eigen;
using namespace std;

// Declarations
void run_monte_carlo_simulation(int n, int K, double(*mypi)(int), double* x, double* p);
double mypi(int N);
double mypi3D(int N);

/** @brief Run repeated Monte Carlo simulations estimating the value of pi
 *  @brief and create three different histograms with n = 2,3,4. Store the x and p values
 *  @brief in the columns of a K per 6 matrix.
*/
Eigen::MatrixXd verifyPi() {
    const int K = 50;  // Number of bins
    Eigen::MatrixXd results(K, 6); // 100 rows, 6 columns

    // Run simulations for n = 2, 3, 4
    for (int i = 0; i < 3; ++i) {
        double *x = results.col(i * 2).data();
        double *p = results.col(i * 2 + 1).data();
        run_monte_carlo_simulation(i + 2, K, mypi, x, p);
    }

    return results;
}

/** @brief Run repeated Monte Carlo simulations estimating the value of pi
 *  @brief and create three different histograms with n = 2,3,4. Store the x and p values
 *  @brief in the columns of a K per 6 matrix.
*/
Eigen::MatrixXd verifyPi3D() {
    const int K = 50;  // Number of bins
    Eigen::MatrixXd results(K, 6); // 100 rows, 6 columns

    // Run simulations for n = 2, 3, 4
    for (int i = 0; i < 3; ++i) {
        double *x = results.col(i * 2).data();
        double *p = results.col(i * 2 + 1).data();
        run_monte_carlo_simulation(i + 2, K, mypi3D, x, p);
    }

    return results;
}

BOOST_PYTHON_MODULE(mypi) {
    using namespace Eigen;
    namespace bp = boost::python;
    eigenpy::enableEigenPy();

    bp::def("verifyPi", verifyPi);
    bp::def("verifyPi3D", verifyPi3D);
}