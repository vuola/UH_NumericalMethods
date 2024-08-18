#include <iostream>
#include <string>
#include <cmath>
#include <numbers>
#include <chrono>
#include <random>
#include <Eigen/Core>
#include <Eigen/Dense>
 
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;

// Random number generator
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 mt(seed);
uniform_real_distribution<double> dist(0.0, 1.0);

// Hard-coded function f 
double f(double x) {
    return sin(exp(-pow(x,2)));
}

// Richardson extrapolation
void derivative(double (*f)(double x), double x, int N, double h, MatrixXd &D) {
    double hh;
    hh=h;
    for (int i=0; i<=N; i++) {
        D(i,0) = (f(x+hh)-f(x-hh))/(2.0*hh);
        for (int j=0; j<=i-1; j++) {
            D(i,j+1) = D(i,j) + (D(i,j)-D(i-1,j))/(pow(4.0,j+1)-1.0);
        }
        hh=hh/2.0;
    }
}

void Spline3_Coeff(int n, VectorXd &x, VectorXd &y, VectorXd &z, double boundary) {
    VectorXd h(n), b(n), u(n), v(n);
    for (int i=0; i<n-1; i++) {
        h(i) = x(i+1) - x(i);
        b(i) = (y(i+1) - y(i))/h(i);
    }
    u(1) = 2.0*(h(0)+h(1));
    v(1) = 6.0*(b(1)-b(0));
    for (int i=2; i<n; i++) {
        u(i) = 2.0*(h(i-1)+h(i)) - h(i-1)*h(i-1)/u(i-1);
        v(i) = 6.0*(b(i)-b(i-1)) - h(i-1)*v(i-1)/u(i-1);
    }
    z(n) = boundary;
    for (int i=n-1; i>0; i--) {
        z(i) = (v(i)-h(i)*z(i+1))/u(i);
    }
    z(0) = boundary;
}

double Spline3_Eval(int n, VectorXd x, VectorXd y, VectorXd z, double x0) {
    int i;
    double h, tmp, result;
    for (i=n-1; i >=0; i--) {
        if (x0-x(i) >= 0) {
            break;
        }
    }
    h = x(i+1) - x(i);
    tmp = 0.5*z(i) + (x0-x(i))*(z(i+1)-z(i))/(6.0*h);
    tmp = -(h/6.0)*(z(i+1)+2.0*z(i)) + (y(i+1)-y(i))/h + (x0-x(i))*tmp;
    result = y(i) + (x0-x(i))*tmp;
    return result;
}

int main(int argc, char *argv[]) {
    int n;
    double boundary;
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " n boundary" << endl;
        return 1;
    }
    n = stoi(argv[1]);
    boundary = stod(argv[2]);

    // Create increasing x and random y values
    VectorXd x(n), y(n);
    for (int i=0; i<n; i++) {
        x(i) = static_cast<double>(i);
        y(i) = dist(mt);
    } 

    return 0;
}