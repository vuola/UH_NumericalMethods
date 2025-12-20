#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <chrono>
#include <vector>
#include <numeric>
#include <algorithm>
#include <sstream>

#define OFFSET_FROM_EXTREMES 0.02

using namespace std;

// Random number generator
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt(seed);
uniform_real_distribution<double> dist(0.0, 1.0);

double getRandomUniform() {
    return dist(mt);
}

/**
 * @file inversecdf.cpp
 * @brief Hard-coded exponential distribution function
 * @param x x-axis value
 * @param lambda rate parameter
 * @return Returns the value of the exponential distribution at x
 */
double exp_dist(double x, double lambda) {
    if (x < 0) return 0;
    return (1/lambda) * exp(-(1/lambda) * x);
}

/**
 * @file inversecdf.cpp
 * @brief Inverse cumulative distribution function of the exponential distribution
 * @param p probability value
 * @param lambda rate parameter
 * @return Returns the inverse cumulative distribution function value at p
 */
double exp_dist_inv(double p, double lambda) {
    if (p < 0 || p > 1) return -1;  // Invalid probability
    return -(lambda) * log(p);
}

/**
 * @file inversecdf.cpp
 * @brief Hard-coded Lorentz distribution function
 * @param x x-axis value
 */
double lorentz_dist(double x) {
    return (1 / M_PI) * (1 / (x * x + 1));
}

/**
 * @file inversecdf.cpp
 * @brief Inverse cumulative distribution function of the Lorentz distribution
 * @param p probability value
 * @return Returns the inverse cumulative distribution function value at p
 */
double lorentz_dist_inv(double p) {
    if (p < 0 || p > 1) return -1;  // Invalid probability
    // Avoid p values too close to 0 or 1
    if (p < OFFSET_FROM_EXTREMES || p > 1 - OFFSET_FROM_EXTREMES) return lorentz_dist_inv(getRandomUniform());
    // Inverse CDF for Lorentz distribution
    return tan(M_PI * (p - 0.5));
}

/**
 * @file inversecdf.cpp
 * @brief Find x value limit based on probability and cumulative distribution function
 * @param p probability value
 * @param F cumulative distribution function F(x)
 * @param x vector of x values
 * @return If successful returns index and corresponding x-value, otherwise
 * @return the returned index is -1
 */
template <typename T, typename Func>
pair<int, T> confidence_limit(double p, const vector<T>& x, Func F) {
    int N = x.size();
    pair<int, T> xlim = {-1, T()};
    for (int i = 0; i < N - 1; ++i) {
        double Fi = F(x[i]);
        double Fi1 = F(x[i + 1]);
        if ((Fi < p) && (Fi1 >= p)) {
            xlim.first = i + 1;
            xlim.second = x[xlim.first];
            break;
        }
    }
    return xlim;
}

/**
 * @file inversecdf.cpp
 * @brief Create an M-bin histogram x and p values from the given data
 * @param data vector of data points
 * @param M number of bins
 * @return Returns a pair of vectors containing x and p values for the histogram
 */
pair<vector<double>, vector<double>> create_histogram(const vector<double>& data, int M) {
    vector<double> x(M);
    vector<double> p(M, 0.0);

    // Compute histogram
    double min_val = *min_element(data.begin(), data.end());
    double max_val = *max_element(data.begin(), data.end());
    double bin_width = (max_val - min_val) / M;

    for (const auto& value : data) {
        int bin = static_cast<int>((value - min_val) / bin_width);
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
        x[i] = min_val + (i + 0.5) * bin_width;
    }

    return {x, p};
}


