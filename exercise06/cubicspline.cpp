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
using Eigen::Ref;
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

void Spline3_Coeff(int n, VectorXd &x, VectorXd &y, Ref<VectorXd> z, double boundary) {
    VectorXd h(n+1), b(n+1), u(n+1), v(n+1);
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

double Spline3_Eval(int n, VectorXd &x, VectorXd &y, Ref<VectorXd> z, double x0) {
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

MatrixXd cubicspline(int n, VectorXd &boundary) {

    // Create increasing x and random y values
    VectorXd x(n), y(n);
    for (int i=0; i<n; i++) {
        x(i) = static_cast<double>(i+1);
        y(i) = dist(mt);
    } 

    // Create output matrix
    MatrixXd out(n+3*(n-1), boundary.size()+1);

    // Compute spline coefficients with different boundary conditions.
    // Store the coefficients in a matrix.
    Eigen::MatrixXd z(n+1, boundary.size());
    for (int i=0; i<boundary.size(); i++) {
        Spline3_Coeff(n, x, y, z.col(i), boundary(i));
    }

    // Evaluate the spline at all x points and three intermediate points between consecutive x values.
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<4; j++) {
            double x0 = x(i) + (x(i+1)-x(i))*j/4.0;
            out(i*4+j,0) = x0;
            for (int k=0; k<boundary.size(); k++) {
                out(i*4+j,k+1) = Spline3_Eval(n, x, y, z.col(k), x0);
            }
            cout << endl;
        }
    }
    // Last point
    int s = n+3*(n-1)-1; 
    out(s,0) = x(n-1);
    for (int k=1; k<=boundary.size(); k++) {
        out(s,k) = y(n-1);
    }

    return out;
}

int main() {
    int n = 10;
    VectorXd boundary {{0.0, 1.0, 10.0}};
    MatrixXd out = cubicspline(n, boundary);
    cout << out << endl;
    return 0;
}