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

/**
 * @brief Create N random numbers and repeat the experiment M times. Calculate averages
 * of the M sets of samples. Store the averages in the provided array.
 * Do another round of random number generation where instead of just a random number, 
 * use the squares of random numbers as input for the statistics. 
 * Store the results in another array.
 * @param N number of random numbers to generate in one experiment
 * @param M number of experiments to run
 * @param averages reference to an array to store M averages
 * @param squared_averages reference to an array to store M squared averages
 * @return Returns 0 if successful
 */
int multipleAverages(int N, int M, double* averages, double* squared_averages) {
    for (int i = 0; i < M; ++i) {
        double sum = 0.0;
        double squared_sum = 0.0;
        for (int j = 0; j < N; ++j) {
            double random_value = getRandomUniform();
            sum += random_value;
            double second_random_value = getRandomUniform();
            squared_sum += second_random_value * second_random_value;
        }
        averages[i] = sum / N;
        squared_averages[i] = squared_sum / N;
    }

    return 0;
}


   



