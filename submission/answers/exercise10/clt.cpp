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
#define MU 0.0
#define SIGMA 1.0

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
 * @file clt.cpp
 * @brief Inverse cumulative distribution function of the exponential distribution
 * @param p probability value
 * @return Returns the inverse cumulative distribution function value at p
 */
double exp_dist_inv(double p) {
    if (p < 0 || p > 1) return -1;  // Invalid probability
    return - (LAMBDA) * log(p);
}


/**
 * @file clt.cpp
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
 * @file gaussrng.cpp
 * @brief Box-Muller transform to generate Gaussian random numbers
 * @param p uniform random number, used to select which sample to output
 * @return Returns a random number from a Gaussian distribution
 */
double gaussrng(double p) {
    double z0, z1;
    // Generate two uniform random numbers
    double u1 = getRandomUniform();
    double u2 = getRandomUniform();

    // Apply the Box-Muller transform
    z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    z1 = sqrt(-2.0 * log(u1)) * sin(2.0 * M_PI * u2);

    // Scale and shift to get the desired mean and standard deviation
    if (p < 0.5) {
        return z0 * SIGMA + MU;
    } else {
        return z1 * SIGMA + MU;
    }
}

/**
 * @brief Create an M-bin histogram x and p values from the given data (using arrays)
 * @param data pointer to array of data points
 * @param data_size number of data points
 * @param M number of bins
 * @param x pointer to array for bin centers (output, size M)
 * @param p pointer to array for probabilities (output, size M)
 */
void create_histogram(const double* data, int data_size, int M, double *x, double *p) {
    // Initialize p
    for (int i = 0; i < M; ++i) {
        p[i] = 0.0;
    }

    // Find min and max
    double min_val = data[0], max_val = data[0];
    for (int i = 1; i < data_size; ++i) {
        if (data[i] < min_val) min_val = data[i];
        if (data[i] > max_val) max_val = data[i];
    }
    double bin_width = (max_val - min_val) / M;

    // Fill histogram
    for (int i = 0; i < data_size; ++i) {
        int bin = static_cast<int>((data[i] - min_val) / bin_width);
        if (bin >= 0 && bin < M) {
            p[bin]++;
        }
    }

    // Normalize probabilities
    double total = 0.0;
    for (int i = 0; i < M; ++i) {
        total += p[i];
    }
    if (total > 0) {
        for (int i = 0; i < M; ++i) {
            p[i] /= total;
        }
    }

    // Compute bin centers
    for (int i = 0; i < M; ++i) {
        x[i] = min_val + (i + 0.5) * bin_width;
    }
}

/**
 * @brief Create K random numbers and calculate the average. Repeat the experiment
 * N times. Store the averages in the provided array.
 * @param K number of random numbers to generate in one averaging experiment
 * @param N number of experiments to run
 * @param rng pointer to the random number generator function to use
 * @param averages reference to an array to store N averages
 * @return Returns 0 if successful
 */
int multipleAverages(int N, int K, double(*rng)(double), double* averages) {
    for (int i = 0; i < N; ++i) {
        double sum = 0.0;
        for (int j = 0; j < K; ++j) {
            double random_value = getRandomUniform();
            sum += rng(random_value);
        }
        averages[i] = sum / K;
    }
    return 0;
}
