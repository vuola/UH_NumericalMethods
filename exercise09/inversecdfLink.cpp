#include <iostream>
#include <utility>
#include <iomanip>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"
using Eigen::MatrixXd;

using namespace Eigen;
using namespace std;

#define RAND_SAMPLES 1000000
#define BINS 20

// Declarations
double getRandomUniform();
double exp_dist(double x, double lambda);
double exp_dist_inv(double p, double lambda);
double lorentz_dist(double x);
double lorentz_dist_inv(double p);
pair<vector<double>, vector<double>> create_histogram(const vector<double>& data, int M);

/**
 * @file problem2Link.cpp
 * @brief Function to create a histogram and verify the distribution
 * @param func_name Name of the distribution function to verify ("exp" or "lorentz")
 * @param M Number of bins for the histogram
 * @return Returns a matrix containing x values, histogram probabilities, and function probabilities
 * @note The function generates random samples, computes the inverse CDF for the specified distribution,
 *       creates a histogram, and compares it with the actual distribution function.
    */

MatrixXd verifyDistribution(string func_name, int M) {

    using namespace std;
    using namespace Eigen;

    vector<double> data(RAND_SAMPLES);
    for (auto& value : data) {
        value = getRandomUniform();
    }

    vector<double> x_values(RAND_SAMPLES);

    if (func_name == "exp") {
        for (int i = 0; i < RAND_SAMPLES; ++i) {
            x_values[i] = exp_dist_inv(data[i], 1.0);  // lambda = 1.0
        }
    } else if (func_name == "lorentz") {
        for (int i = 0; i < RAND_SAMPLES; ++i) {
            x_values[i] = lorentz_dist_inv(data[i]);
        }
    } else {
        cerr << "Unknown function: " << func_name << ". Use 'exp' or 'lorentz'.\n";
        return 0.0 * MatrixXd::Zero(3, M);  // Return empty matrix on error
    }

    auto [x_hist, p_hist] = create_histogram(x_values, M);

    vector<double> p_func(M);
    if (func_name == "exp") {
        for (int i = 0; i < M; ++i) {
            p_func[i] = exp_dist(x_hist[i], 1.0);
        }
    } else {
        for (int i = 0; i < M; ++i) {
            p_func[i] = lorentz_dist(x_hist[i]);
        }
    }
    double integral = accumulate(p_func.begin(), p_func.end(), 0.0);
    if (integral > 0) {
        for (auto& prob : p_func) {
            prob /= integral;
        }
    }

    MatrixXd result(3, M);
    cout << fixed << setprecision(6);
    for (int i = 0; i < M; ++i) {
        result(0, i) = x_hist[i];
        result(1, i) = p_hist[i];
        result(2, i) = p_func[i];
    }
    return result;
}


BOOST_PYTHON_MODULE(inversecdf) {
  using namespace Eigen;
  namespace bp = boost::python;
  eigenpy::enableEigenPy();

  bp::def("verifyDistribution", verifyDistribution);
}