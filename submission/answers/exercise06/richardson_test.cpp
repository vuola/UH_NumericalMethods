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
    return sin(exp(-pow(x,2)));
}

// Hard-coded derivative of f
double df(double x) {
    return -2*x*exp(-pow(x,2))*cos(exp(-pow(x,2)));
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

// Reference derivative using central difference
double central_diff(double (*f)(double x), double x, double h) {
    return (f(x+h)-f(x-h))/(2.0*h);
}

int main() {
    int N=5;
    double h, x=1.0;
    MatrixXd D(N+1,N+1);

    // Test Richardson derivative for different values of h
    cout << "Testing Richardson derivative for different values of h" << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "n\t" << "h=10^(-n)\t" << "Richardson error\t" << "Central difference error" << endl << endl;

    for (int n=4; n<=14; n=n+2) {
        h = pow(10.0,-n);
        derivative(f, x, N, h, D);
        cout << n << "\t" << h << "\t\t" << D(N,N)-df(x) << "\t\t" << central_diff(f, x, h)-df(x) << endl;
    }


    return 0;
}