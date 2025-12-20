#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <sstream>

using namespace std;

// Random number generator
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt(seed);
uniform_real_distribution<double> dist(0.0, 1.0);

double getRandomUniform() {
    return dist(mt);
}


/** @brief Estimate the value of pi using Monte Carlo simulation
 *  @param N Number of random points to generate
 *  @return Estimated value of pi
 */
double mypi(int N) {
    double sum = 0.0;
    for (int i = 0; i < N; ++i) {
        double x = getRandomUniform();
        double y = getRandomUniform();
        if (x * x + y * y <= 1.0) {
            sum += 1.0;
        }
    }
    return 4.0 * sum / N;
}

/** @brief Estimate the value of pi using 3D Monte Carlo simulation
 *  @param N Number of random points to generate
 *  @return Estimated value of pi
 */
double mypi3D(int N) {
    double inside = 0.0;
    for (int i = 0; i < N; ++i) {
        double x = getRandomUniform();
        double y = getRandomUniform();
        double z = getRandomUniform();
        if (x * x + y * y + z * z <= 1.0) {
            inside += 1.0;
        }
    }
    return (6.0 * inside) / N;
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
    double total = 0.0;
    for (int i = 0; i < K; ++i) {
        total += p[i];
    }
    if (total > 0) {
        for (int i = 0; i < K; ++i) {
            p[i] /= total;
        }
    }

    // Compute bin centers
    for (int i = 0; i < K; ++i) {
        x[i] = min_val + (i + 0.5) * bin_width;
    }
}


/**
 * @brief Run repeated Monte Carlo simulations estimating the value of pi
 * @brief and form a histogram based on 1000 resulting pi values. Each pi value
 * @brief is formed using N random numbers. 
 * @param n exponent for number of samples used for obtaining one estimate of pi, N = 10^n
 * @param K number of histogram bins in the output
 * @param mypi pointer to the function used to estimate pi
 * @return arrays x and p representing the histogram
 */
void run_monte_carlo_simulation(int n, int K, double(*mypi)(int), double* x, double* p) {
    int N = pow(10, n);
    double *pi_values = new double[1000];
    for (int i = 0; i < 1000; ++i) {
        pi_values[i] = mypi(N);
    }
    create_histogram(pi_values, 1000, K, x, p);
    delete[] pi_values;
}