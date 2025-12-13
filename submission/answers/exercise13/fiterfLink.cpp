#include <iostream>
#include <utility>
#include <iomanip>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"

using namespace Eigen;
using namespace std;

// Declarations
double* fiterf(int n, char model_type);

/**
 * @file fiterfLink.cpp
 * @brief evaluates fiterf, creates k datapoints between 0 and 1, evaluates erf and the fitted values in the k points. Model parameters are printed to standard output.
 * @param n number of parameters
 * @param model_type type of mode:
 * @param   'a' : polynomial of degree n-1
 * @param   'b' : polynomial with odd powers only: y = p_1*x + p_2*x^3 + ... + p_n*x^(2n-1) 
 * @param   'c' : using z = 1/(1+x), y = p_1 + exp(-x^2)*(p_2 + p_3*z + p_4*z^2 + ... + p_n*z^(n-2))
 * @param k number of datapoints to evaluate
 * @return A k x 3 matrix. The first column contains the x values, the second column the erf(x) values, and the third column the fitted values.
*/

Eigen::MatrixXd evaluateFiterf(int n, char model_type, int k) {
    double* params = fiterf(n, model_type);

    cout << "Fitted parameters model " << model_type << " n=" << n << endl;
    for (int i = 0; i < n; ++i) {
        cout << "p[" << i << "] = " << params[i] << endl;
    }

    Eigen::MatrixXd results(k, 3);
    for (int i = 0; i < k; ++i) {
        double x = static_cast<double>(i) / (k - 1);
        double erf_val = erf(x);
        double fitted_val = 0.0;
        double z = 1.0 / (1.0 + x);

        for (int j = 0; j < n; ++j) {
            double term = 0.0;
            if (model_type == 'a') {
                term = params[j] * pow(x, j);
            } else if (model_type == 'b') {
                term = params[j] * pow(x, 2 * j + 1);
            } else if (model_type == 'c') {
                if (j == 0) {
                    term = params[j];
                } else {
                    term = params[j] * exp(-x * x) * pow(z, j - 1);
                }
            }
            fitted_val += term;
        }

        results(i, 0) = x;
        results(i, 1) = erf_val;
        results(i, 2) = fitted_val;
    }

    delete[] params;
    return results;
} 


BOOST_PYTHON_MODULE(fiterf) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("evaluateFiterf", evaluateFiterf);
}