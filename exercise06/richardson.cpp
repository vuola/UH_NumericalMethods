#include <iostream>
#include <string>
#include <cmath>
#include <numbers>
#include <Eigen/Core>
#include <Eigen/Dense>
 
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;


// Hard-coded function f 
double f(double x) {
    return sin(exp(pow(-x,2)));
}

// Hard-coded derivative of f
