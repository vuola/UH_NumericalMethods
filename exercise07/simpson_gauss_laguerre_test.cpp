#include <iostream>
#include <string>
#include <cmath>
#include <numbers>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iomanip>
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;


// Hard-coded function f 
double f(double x) {
    return exp(-x) * pow(cos(x),2);
}

// Hard-coded function with definite upper limit
double f_definite(double t) {
   return exp(-t*(1.0-t)) * pow(cos(t / (1.0-t)), 2) * pow(1.0-t, -2); 
}

// Hard-coded function for Gauss-Laguerre quadrature
double f_gauss_laguerre(double x) {
    return pow(cos(x), 2);
}


// Adaptive Simpson's rule
double Simpson(double (*f)(double x), double a, double b, double eps, int level, int level_max)
{
    int i, j, k, kmax=1;
    double c, d, e, h, result;
    double one_simpson, two_simpson;
    double left_simpson, right_simpson;
    h = b-a;
    c = 0.5*(a+b);
    one_simpson = h*(f(a)+4.0*f(c)+f(b))/6.0;
    d = 0.5*(a+c); e = 0.5*(c+b);
    two_simpson = h*(f(a)+4.0*f(d)+2.0*f(c)+4.0*f(e)+f(b))/12.0;

    /* Check for level */
    if (level+1 >= level_max) {
        result = two_simpson;
    } else {

        /* Check for desired accuracy */
        if (fabs(two_simpson-one_simpson) < 15.0*eps)
            result = two_simpson + (two_simpson-one_simpson)/15.0;

        /* Divide further */
        else {
            left_simpson = Simpson(f,a,c,eps/2.0,level+1,level_max);
            right_simpson = Simpson(f,c,b,eps/2.0,level+1,level_max);
            result = left_simpson + right_simpson;
        }
    }
    return(result);
}

// Gauss-Laguerre guadrature for 2, 4 and 8 points
double qgaus(double (*func)(double), int n)
{
    static double x2[]={0.58578644, 3.41421356};
    static double w2[]={0.85355339, 0.14644661};
    static double x4[]={0.32254769, 1.7457611,  4.5366203,  9.39507091};
    static double w4[]={6.03154104e-01, 3.57418692e-01, 3.88879085e-02, 5.39294706e-04};
    static double x8[]={0.17027963, 0.90370178, 2.25108663, 4.26670017, 7.0459054, 10.75851601, 15.74067864, 22.86313174};
    static double w8[]={3.69188589e-01, 4.18786781e-01, 1.75794987e-01, 3.33434923e-02, 2.79453624e-03, 9.07650877e-05, 8.48574672e-07, 1.04800117e-09};

    // Evaluate the integral using Gauss-Laguerre quadrature in the range [0, Inf) using 2, 4, and 8 points
    double result = 0.0;
    if (n == 2) {
        for (int i = 0; i < 2; ++i) {
            result += w2[i] * func(x2[i]);
        }
    } else if (n == 4) {
        for (int i = 0; i < 4; ++i) {
            result += w4[i] * func(x4[i]);
        }
    } else if (n == 8) {
        for (int i = 0; i < 8; ++i) {
            result += w8[i] * func(x8[i]);
        }
    } else {
        cerr << "Invalid number of points for Gauss-Laguerre quadrature. Use 2, 4, or 8." << endl;
        return NAN;
    }
    return result;
}


int main() {
    int level_max = 20; // Maximum recursion level for Simpson's method
    double a = 0.0, b = 1.0, eps = 1e-9;

    cout << "Adaptive Simpson's method" << endl;
    cout << "The expected result is: 0.6" << endl; // Known value for this integral
    cout << "maximum error setting: eps = " << eps << endl;
    // b = 1.0
    cout << "Integrating f(x) = exp(-x) * cos(x)^2 from " << a << " to different upper limits" << endl;
    double result = Simpson(f, a, b, eps, 0, level_max);
    cout << b << ":  " << setw(8) << result << "    error: " << fabs(result - 0.6) << endl;
    b = 10.0;
    result = Simpson(f, a, b, eps, 0, level_max);
    cout << b << ": " << setw(8) << result << "    error: " << fabs(result - 0.6) << endl;
    b = 100.0;
    result = Simpson(f, a, b, eps, 0, level_max);
    cout << b << ":" << setw(8) << result << "    error: " << fabs(result - 0.6) << endl << endl;
    cout << "---------------------------------" << endl;

    // Testing with definite upper limit
    cout << "Adaptive Simpson's method with definite upper limit" << endl;
    cout << "when b = 1.0 the expected result is: 0.6" << endl; // Known value for this integral
    a = 0.0;
    cout << "Integrating f(t) = exp(-t*(1-t)) * cos(t*(1-t))^2 * (1-t)^-2 from " << a << " to upper limits approaching 1" << endl;
    cout << "Maximum number of recursion levels: " << level_max << endl;
    b = 0.99;
    result = Simpson(f_definite, a, b, eps, 0, level_max);
    cout << b << ":  " << setw(8) << result << "    error: " << fabs(result - 0.6) << endl;
    b = 0.75;
    result = Simpson(f_definite, a, b, eps, 0, level_max);
    cout << b << ":  " << setw(8) << result << "    error: " << fabs(result - 0.6) << endl;
    b = 0.625;
    result = Simpson(f_definite, a, b, eps, 0, level_max);
    cout << b << ":  " << setw(8) << result << "    error: " << fabs(result - 0.6) << endl;
    b = 0.5625;
    result = Simpson(f_definite, a, b, eps, 0, level_max);
    cout << b << ":  " << setw(8) << result << "    error: " << fabs(result - 0.6) << endl;
    b = 0.5001;
    result = Simpson(f_definite, a, b, eps, 0, level_max);
    cout << b << ":  " << setw(8) << result << "    error: " << fabs(result - 0.6) << endl;
    b = 0.5;
    result = Simpson(f_definite, a, b, eps, 0, level_max);
    cout << b << ":  " << setw(8) << result << "    error: " << fabs(result - 0.6) << endl;
    b = 0.49;
    result = Simpson(f_definite, a, b, eps, 0, level_max);
    cout << b << ":  " << setw(8) << result << "    error: " << fabs(result - 0.6) << endl;
    cout << "---------------------------------" << endl << endl;

    // Testing Gauss-Laguerre quadrature
    cout << "Testing Gauss-Laguerre quadrature" << endl;
    cout << "The expected result is: 0.6" << endl; // Known value for this integral
    cout << "Integrating f(x) = exp(-x) * cos(x)^2 from 0 to Inf with different number of points" << endl;
    double result_gauss_2 = qgaus(f_gauss_laguerre, 2);
    double result_gauss_4 = qgaus(f_gauss_laguerre, 4);
    double result_gauss_8 = qgaus(f_gauss_laguerre, 8);
    cout << "2: " << result_gauss_2 << "    error: " << fabs(result_gauss_2 - 0.6) << endl;
    cout << "4: " << result_gauss_4 << "    error: " << fabs(result_gauss_4 - 0.6) << endl;
    cout << "8: " << result_gauss_8 << "    error: " << fabs(result_gauss_8 - 0.6) << endl;
    return 0;
}