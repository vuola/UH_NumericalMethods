#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <numeric>
#include <algorithm>
#include <sstream>


#define RAND_SAMPLES 1000000
#define OFFSET_FROM_EXTREMES 0.1
#define BINS 20

using namespace std;

// Random number generator
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt(seed);
uniform_real_distribution<double> dist(0.0, 1.0);

double getRandomUniform() {
    return dist(mt);
}

/**
 * @file problem2.cpp
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
 * @file problem2.cpp
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
 * @file problem2.cpp
 * @brief Hard-coded Lorentz distribution function
 * @param x x-axis value
 */
double lorentz_dist(double x) {
    return (1 / M_PI) * (1 / (x * x + 1));
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
    if (p < OFFSET_FROM_EXTREMES) p = OFFSET_FROM_EXTREMES;
    if (p > 1 - OFFSET_FROM_EXTREMES) p = 1 - OFFSET_FROM_EXTREMES;
    // Inverse CDF for Lorentz distribution
    return tan(M_PI * (p - 0.5));
}

/**
 * @file problem2.cpp
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
 * @file problem2.cpp
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


/**
 * @file problem2.cpp
 * @brief Main function to demonstrate the functionality
    */

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <exp|lorentz>\n";
        return 1;
    }
    string func_name = argv[1];

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
        return 1;
    }

    int M = BINS;  // Number of bins for histogram
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

    cout << fixed << setprecision(6);
    cout << "x_hist\tp_hist\tp_" << func_name << "\n";
    for (int i = 0; i < M; ++i) {
        cout << x_hist[i] << "\t" << p_hist[i] << "\t" << p_func[i] << "\n";
    }
}