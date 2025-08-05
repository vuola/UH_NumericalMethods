#include <iostream>
#include <cmath>
#include <numbers>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_errno.h>
using namespace std;

// Declarations
// Generic gradient descent minimization algorithm
int gradient(double x0, double y0, const gsl_multimin_fdfminimizer_type *T);
// Generic simplex minimization algorithm
int simplex(double x0, double y0, const gsl_multimin_fminimizer_type *T);


// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "minimize - find the minimum of a function using GSL minimization algorithms" << endl << endl;
    cout << "Usage:" << endl;
    cout << "  minimize x0 y0 alg" << endl;
    cout << "  minimize --help" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl;
    cout << "Arguments:" << endl;
    cout << "  x0           initial x coordinate of the point to be minimized" << endl;
    cout << "  y0           initial y coordinate of the point to be minimized" << endl;
    cout << "  alg          algorithm to be used for minimization (1-4)" << endl;
    cout << "              1 - Nelder-Mead simplex method" << endl;
    cout << "              2 - steepest descent method" << endl;
    cout << "              3 - Polak-Ribiere conjugate gradient method" << endl;
    cout << "              4 - Broyden-Fletcher-Goldfarb-Shanno (BFGS) method" << endl;
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

// Selection of the minimization algorithm and starting position
/**
* @brief Use one of four GSL minimization algorithms to minimize function f(x, y).
* @return A pair containing the x and y coordinates of the minimum point.
* @throws std::invalid_argument if the interval is not valid.
* @param x0 - initial x coordinate of the point to be minimized
* @param y0 - initial y coordinate of the point to be minimized
* @param alg - algorithm to be used for minimization 
*              1 - Nelder-Mead simplex method
*              2 - steepest descent method
*              3 - Polak-Ribiere conjugate gradient method
*              4 - Broyden-Fletcher-Goldfarb-Shanno (BFGS) method
*/
int minimize(double x0, double y0, int alg) {
    switch (alg) {
        case 1:
            // Call Nelder-Mead simplex method
            simplex(x0, y0, gsl_multimin_fminimizer_nmsimplex2);
            break;
        case 2:
            // Call steepest descent method
            gradient(x0, y0, gsl_multimin_fdfminimizer_steepest_descent);
            break;
        case 3:
            // Call Polak-Ribiere conjugate gradient method
            gradient(x0, y0, gsl_multimin_fdfminimizer_conjugate_pr);
            break;
        case 4:
            // Call Broyden-Fletcher-Goldfarb-Shanno (BFGS) method
            gradient(x0, y0, gsl_multimin_fdfminimizer_vector_bfgs2);
            break;
        default:
            throw std::invalid_argument("Invalid algorithm selection");
    }
    return 0;
}

// Main function implementing command line 
int main(int argc, char** argv){

    if (argc == 1) {
        cerr << getArgumentCountErrorMessage(argv[0], 2, argc - 1) << endl;
        return 1;
    }

    string flag = argv[1];

    if (flag == "--help" || flag == "-h" || flag == "-H") {
        displayHelp();
        return 0;
    }

    if (argc == 4) {
        double arg1 = stod(argv[2]);
        double arg2 = stod(argv[3]);
        int alg = stoi(argv[4]);
        minimize(arg1, arg2, alg);
        return 0;
    }

    cerr << getArgumentCountErrorMessage(argv[0], 4, argc - 1) << endl;
    return 1;

}