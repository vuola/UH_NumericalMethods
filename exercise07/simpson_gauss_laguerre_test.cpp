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
    return exp(-x) * pow(cos(x),2);
}

// Hard-coded function with definite upper limit
double f_definite(double t) {
   return exp(-t*(1.0-t)) * pow(cos(t / (1.0-t)), 2) * pow(1.0-t, -2); 
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
        printf("Maximum level reached\n");
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

// Gauss-Laguerre guadrature
double qgaus(double (*func)(double), double a, double b)
{
    int j;
    double xr,xm,dx,s;
    static double x[]={0.0, 0.1488743389, 0.4333953941, 0.6794095682, 0.8650633666, 0.9739065285};
    static double w[]={0.0, 0.2955242247, 0.2692667193, 0.2190863625, 0.1494513491, 0.0666713443};
    xm=0.5*(b+a);
    xr=0.5*(b-a);
    s=0;
    for (j=1;j<=5;j++) {
        dx=xr*x[j];
        s += w[j]*((*func)(xm+dx)+(*func)(xm-dx));
    }
    return s *= xr;
}


int main() {
    int level_max = 20;
    double a = 0.0, b = 1.0, eps = 1e-9;

    cout << "Testing Adaptive Simpson's method" << endl << endl;
    cout << "when b = Inf the expected result is: 0.6" << endl; // Known value for this integral
    cout << "maximum error setting: eps = " << eps << endl;
    cout << "---------------------------------" << endl;
    // b = 1.0
    cout << "Integrating f(x) = exp(-x) * cos(x)^2 from " << a << " to " << b << endl;
    double result = Simpson(f, a, b, eps, 0, level_max);
    cout << "Result: " << result << endl;
    cout << "Error: " << fabs(result - 0.6) << endl << endl;
    // b = 10.0
    b = 10.0;
    cout << "Integrating f(x) = exp(-x) * cos(x)^2 from " << a << " to " << b << endl;
    result = Simpson(f, a, b, eps, 0, level_max);
    cout << "Result: " << result << endl;
    cout << "Error: " << fabs(result - 0.6) << endl << endl;
    // b = 100.0
    b = 100.0;
    cout << "Integrating f(x) = exp(-x) * cos(x)^2 from " << a << " to " << b << endl;
    result = Simpson(f, a, b, eps, 0, level_max);
    cout << "Result: " << result << endl;
    cout << "Error: " << fabs(result - 0.6) << endl;
    cout << "---------------------------------" << endl << endl;

    // Testing with definite upper limit
    cout << "Testing Adaptive Simpson's method with definite upper limit" << endl << endl;
    cout << "when b = 1.0 the expected result is: 0.6" << endl; // Known value for this integral
    cout << "Integrating f(t) = exp(-t*(1-t)) * cos(t*(1-t))^2 * (1-t)^-2 from 0 to 1" << endl;
    a = 0.0;
    b = 1.0;
    result = Simpson(f_definite, a, b, eps, 0, level_max);
    cout << "Result: " << result << endl;   
    cout << "Error: " << fabs(result - 0.6) << endl;
    cout << "---------------------------------" << endl << endl;

    // Testing Gauss-Laguerre quadrature
    cout << "Testing Gauss-Laguerre quadrature" << endl << endl;
    cout << "when b = Inf the expected result is: 0.6" << endl; // Known value for this integral
    cout << "Integrating f(x) = exp(-x) * cos(x)^2 from 0 to Inf using Gauss-Laguerre quadrature" << endl;
    a = 0.0;
    b = 100.0; // Not used in Gauss-Laguerre, but kept for consistency
    result = qgaus(f, a, b);
    cout << "Result: " << result << endl;
    cout << "Error: " << fabs(result - 0.6) << endl;
    cout << "---------------------------------" << endl;

    return 0;
}