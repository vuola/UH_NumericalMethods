#include <iostream>
#include <string>
#include <cmath>
#include <complex>
#include <numbers>
#include <Eigen/Core>
 
using Eigen::MatrixXd;
using Eigen::VectorXd;
 
using namespace std;
using namespace std::numbers;


// Hard-coded function for exercise 4 problem 3B
double f(double x, double mu) {
    double m = (mu*(x-1)+1)/x;
    double ex = 1/(mu-1);
    std::complex<double> y = std::pow(m,ex); 
    double out = real(y);
    return out;
}


// Hard-coded f derivative for exercise 4 problem 3B
double df(double x, double mu) {
    double num2 = mu*(x-1)+1;
    double den2 = x;
    double exp2 = 1/(mu-1);
    double num1 = pow(num2/den2, exp2);
    double den1 = mu*(x-1)*x+x;
//    std::complex<double> term1 = std::pow(m1,e1);
//    std::complex<double> term2 = std::pow(x,e2);
    return num1 / den1;
}

/**
 * @brief
 * frange - evaluate function in a range with starting parameters 
 * @return  
 * Returns Matrix m where number of rows is length(mu) + 1 and
 * number of columns is defined by N (number of x points).
 * The first row contains x values, where the N points are spread out evenly in 
 * the range [x_left, x_right].
 * Starting from second row are the y values, one row for each mu parameter.
 *   
 * @throws None.
 * @param mu vector of values for parameter mu, each element adds a row to output.
 * @param x_left starting value for x
 * @param x_right ending value for x
 * @param N number of input variable points between [x_left, x_right]  
 * 
 **/
MatrixXd frange(VectorXd mu, double x_left, double x_right, int N) {

    int m = mu.size() + 1;
    MatrixXd out(m, N);
    VectorXd Xpoints = VectorXd::LinSpaced(N, x_left, x_right);

    // main loop       
    for (int i=0; i<N; ++i) {
        out(0,i) = Xpoints(i);
        for (int j=0; j<mu.size(); ++j) {
            out(j+1,i) = f(out(0,i), mu(j));
        }
    }
    return out;
}

/**
 * @brief
 * fractal_1 - evaluate convergence of a series producing fractal 
 * @return  
 * Returns x(N) i.e. the N:th iteration of x value for series:
 * x(k+1) = mu * x(k) * {1 - x(k)}
 *  
 * @throws None.
 * @param x0 starting x-value for search 
 * @param mu constant used in iteration
 **/
double fractal_1(double x0, double mu) {

    int imax = 60;
    double tolerance = 1.0e-9; 
    double x2, diff;

    // initialize
    double x1 = x0;

    // main loop       
    for (int i=0; i<imax; ++i) {
        x2 = mu * x1 * (1 - x1);
        diff = x2 - x1;
        // check if root is close enough
        if (abs(diff) < tolerance) break;
        x1 = x2;
    }
    return x2;
}

/**
 * @brief
 * fractal_2 - use Newton method to find solution to f(x) = 0 starting from x0 
 * @return  
 * Returns x fulfilling f(x) = 0. The Newton iteration for finding the root is
 * x(k+1) = x(k) - f{x(k)}/f'{x(k)} 
 * Functions f = f(x,mu) and f' = df(x,mu) are hard-coded. 
 * @throws None.
 * @param x0 starting x-value for search 
 * @param mu constant used in f() and df()
 **/
double fractal_2(double x0, double mu) {

    int imax = 60;
    double tolerance = 1.0e-9; 
    double fmid, dfmid;

    // initialize
    double xmid = x0;

    // cout << "round\t" << "x\t\t" << "f(x)\t\t" << "f'(x)\t" << "mu" << endl;

    // main loop       
    for (int i=0; i<imax; ++i) {
        fmid = f(xmid, mu);
        dfmid = df(xmid, mu);
        // cout << i << "\t" << xmid << "\t" << fmid << "\t" << dfmid << "\t" << mu << endl;
        xmid = xmid - (fmid / dfmid);
        // check if root is close enough
        if (abs(fmid) < tolerance) break;
    }
    return xmid;
}

/**
 * @brief
 * bifurcation - evaluate bifurcating series 
 * @return  
 * Returns Matrix m where number of rows is 3 and
 * number of columns is defined by N (number of mu points).
 * The first row contains mu values, where the N points are spread out evenly in 
 * the range [mu_left, mu_right].
 * Starting from second row are the series x(N) values. First series uses a known
 * fractal series formula, second series is the same but represented as a newton 
 * iteration.
 *   
 * @throws None.
 * @param x0 starting value for the x-iteration formula
 * @param mu_left starting value for mu
 * @param mu_right ending value for mu
 * @param N number of mu points between [mu_left, mu_right]  
 * 
 **/
MatrixXd bifurcation(double x0, double mu_left, double mu_right, int N) {

    MatrixXd out(3, N);
    VectorXd muPoints = VectorXd::LinSpaced(N, mu_left, mu_right);

    // main loop       
    for (int i=0; i<N; ++i) {
        out(0,i) = muPoints(i);
        out(1,i) = fractal_1(x0, muPoints(i));
        out(2,i) = fractal_2(x0, muPoints(i));
    }
    return out;
}