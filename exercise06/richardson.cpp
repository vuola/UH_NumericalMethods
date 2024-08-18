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

int main(int argc, char *argv[]) {
    int N;
    double h, x;
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " N h x" << endl;
        return 1;
    }
    N = stoi(argv[1]);
    h = stod(argv[2]);
    x = stod(argv[3]);
    MatrixXd D(N+1,N+1);
    derivative(f, x, N, h, D);
    cout << D << endl << endl;
    cout << "Richardson derivative of f at x = " << x << " is " << D(N,N) << endl;
    return 0;
}