#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <chrono>
#include <vector>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <Eigen/Core>
#include "eigenpy/eigenpy.hpp"
using Eigen::MatrixXd;

#define OFFSET_FROM_EXTREMES 0.1

using namespace std;
using namespace Eigen;

// Random number generator
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt(seed);
uniform_real_distribution<double> dist(0.0, 1.0);

double getRandomUniform() {
    return dist(mt);
}

/**
 * @file gaussrng.cpp
 * @brief Hard-coded Lorentz distribution function
 * @param x x-axis value
 * @param lambda rate parameter
 */

double lorentzDist(double x, double lambda) {
    return (1.0 / M_PI) * (lambda / ((x * x) + (lambda * lambda)));
}

/**
 * @file gaussrng.cpp
 * @brief Box-Muller transform to generate Gaussian random numbers
 * @param mu mean of the distribution
 * @param sigma standard deviation of the distribution
 * @return Returns a random number from a Gaussian distribution
 */
pair<double, double> gaussrng(double mu, double sigma) {
    double z0, z1;
    // Generate two uniform random numbers
    double u1 = getRandomUniform();
    double u2 = getRandomUniform();

    // Apply the Box-Muller transform
    z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    z1 = sqrt(-2.0 * log(u1)) * sin(2.0 * M_PI * u2);

    // Scale and shift to get the desired mean and standard deviation
    return make_pair(z0 * sigma + mu, z1 * sigma + mu);
} 


/**
 * @file gaussrng.cpp
 * @brief Create an M-bin histogram x and p values from the given data
 * @param data vector of data points
 * @param M number of bins
 * @param min_x minimum x value for histogram
 * @param max_x maximum x value for histogram
 * @return Returns a pair of vectors containing x and p values for the histogram
 */
pair<vector<double>, vector<double>> create_histogram(const vector<double>& data, int M, double min_x = -10.0, double max_x = 10.0) {
    vector<double> x(M);
    vector<double> p(M, 0.0);

    // Compute histogram
    double bin_width = (max_x - min_x) / M;

    for (const auto& value : data) {
        int bin = static_cast<int>((value - min_x) / bin_width);
        if (bin >= 0 && bin < M) {
            p[bin]++;
        }
    }

    // Normalize probabilities
    double total = accumulate(p.begin(), p.end(), 0.0);
    if (total > 0) {
        for (auto& prob : p) {
            prob /= total;
        }
    }

    // Compute bin centers
    for (int i = 0; i < M; ++i) {
        x[i] = min_x + (i + 0.5) * bin_width;
    }

    return {x, p};
}

/**
 * @file gaussrng.cpp
 * @brief Function to create data following the Lorentz distribution by ration of two gaussian variables. The distribution is verified by comparing histogram with the actual distribution function.
 * @param M Number of bins for the histogram
 * @param N Number of samples to generate
 * @param min_val Minimum x value for histogram
 * @param max_val Maximum x value for histogram
 * @return Returns a matrix containing x values, histogram probabilities, and function probabilities
 */
MatrixXd verifyLorentzDistribution(int M, int N, double min_x, double max_x) {

    vector<double> data(N);
    for (auto& value : data) {
        auto [z0, z1] = gaussrng(0.0, 1.0);
        value = z0 / z1;  // Generate Lorentz distribution by ratio of two Gaussian variables
    }

    vector<double> x_values(N);
    for (int i = 0; i < N; ++i) {
        x_values[i] = data[i];
    }

    auto [x_hist, p_hist] = create_histogram(x_values, M, min_x, max_x);

    vector<double> p_func(M);
    for (int i = 0; i < M; ++i) {
        p_func[i] = lorentzDist(x_hist[i], 1.0);  // lambda = 1.0
    }
    
    double integral = accumulate(p_func.begin(), p_func.end(), 0.0);
    if (integral > 0) {
        for (auto& prob : p_func) {
            prob /= integral;
        }
    }

    MatrixXd result(3, M);
    for (int i = 0; i < M; ++i) {
        result(0, i) = x_hist[i];
        result(1, i) = p_hist[i];
        result(2, i) = p_func[i];
    }

    return result;
}
