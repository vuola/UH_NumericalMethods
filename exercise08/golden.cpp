#include <iostream>
#include <cmath>
#include <numbers>
// #include <Eigen/Core>
// #include <Eigen/Dense>
// #include <iomanip>
// using Eigen::VectorXd;

using namespace std;

// Hard-coded function for exercise 8 problem 4
double f(double x) {
    return pow(x, 4) - sin(x);
}

// Golden section minimization algorithm
/**
* @brief Golden section search for finding the minimum of a function.
* @return The x-coordinate of the minimum point.
* @throws std::invalid_argument if the interval is not valid.
* @param xa - left endpoint of the interval
* @param xc - right endpoint of the interval
*/
double golden(double xa, double xc) {
    const double phi = (1 + sqrt(5)) / 2; // Golden ratio
    double xb = xc - (xc - xa) / phi;
    double xd = xa + (xc - xa) / phi;
    double fxb = f(xb);
    double fxd = f(xd);

    while (abs(xc - xa) > 1e-9) {
        if (fxb < fxd) {
            xc = xd;
            xd = xb;
            xb = xc - (xc - xa) / phi;
            fxd = fxb;
            fxb = f(xb);
        } else {
            xa = xb;
            xb = xd;
            xd = xa + (xc - xa) / phi;
            fxb = fxd;
            fxd = f(xd);
        }
    }
    return (xa + xc) / 2; // Return the minimum point
}



