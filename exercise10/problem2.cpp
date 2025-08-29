#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <sstream>

#define OFFSET_FROM_EXTREMES 0.02
#define LAMBDA 1.0

using namespace std;

// Random number generator
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt(seed);
uniform_real_distribution<double> dist(0.0, 1.0);

double getRandomUniform() {
    return dist(mt);
}

double uniform(double p) {
    return p - 0.5;
}

/**
 * @file problem2.cpp
 * @brief Inverse cumulative distribution function of the exponential distribution
 * @param p probability value
 * @return Returns the inverse cumulative distribution function value at p
 */
double exp_dist_inv(double p) {
    if (p < 0 || p > 1) return -1;  // Invalid probability
    return - (LAMBDA) * log(p);
}


/**
 * @file problem2.cpp
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
 * @brief Create an M-bin histogram x and p values from the given data (using arrays)
 * @param data pointer to array of data points
 * @param data_size number of data points
 * @param K number of bins
 * @param x pointer to array for bin centers (output, size M)
 * @param p pointer to array for probabilities (output, size M)
 */
void create_histogram(const double* data, int data_size, int K, double* x, double* p) {
    // Initialize p
    for (int i = 0; i < K; ++i) {
        p[i] = 0.0;
    }

    // Find min and max
    double min_val = data[0], max_val = data[0];
    for (int i = 1; i < data_size; ++i) {
        if (data[i] < min_val) min_val = data[i];
        if (data[i] > max_val) max_val = data[i];
    }
    double bin_width = (max_val - min_val) / K;

    // Fill histogram
    for (int i = 0; i < data_size; ++i) {
        int bin = static_cast<int>((data[i] - min_val) / bin_width);
        if (bin >= 0 && bin < K) {
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

/**
 * @brief Create N random numbers and repeat the experiment M times. Calculate averages
 * of the M sets of samples. Store the averages in the provided array.
 * @param N number of random numbers to generate in one experiment
 * @param M number of experiments to run
 * @param rng pointer to the random number generator function to use
 * @param averages reference to an array to store M averages
 * @return Returns 0 if successful
 */
int multipleAverages(int N, int M, double(*rng)(double), double* averages) {
    for (int i = 0; i < M; ++i) {
        double sum = 0.0;
        for (int j = 0; j < N; ++j) {
            double random_value = getRandomUniform();
            sum += rng(random_value);
        }
        averages[i] = sum / N;
    }
    return 0;
}
