#include <iostream>
#include "rungeKuttaSolver.cpp"
using namespace std;

/**
 * @brief g - the function for which we want to find the root
 * @param k the shooting parameter
 * @param a the start of the interval
 * @param b the end of the interval
 * @param N the number of steps
 * @param ya the boundary condition at x=a
 * @param yb the boundary condition at x=b
 * @param x array to store x values
 * @param y array to store y values
 * @return Returns g(k).
 */
double g(double k, double a, double b, int N, double ya, double yb, double* x, double* y) {

    // Solve the ODE y''(x) + y(x) = 0 using the shooting method.
    // The parameter k is the initial slope y'(a).
    // Solve the ODE using Runge-Kutta method
    rungeKuttaSolver(a, b, N, ya, k, x, y);

    // Compute g(k) = y(b) - desired boundary value at x=b
    double gk = y[N] - yb;

    return gk;
}


/**
 * @brief bisect_g - find solution to g(k) = 0 between k = [k1, ..., k2] 
 * @param k1 left edge (k-value) of search bracket
 * @param k2 right edge (k-value) of search bracket
 * @param a the start of the interval
 * @param b the end of the interval
 * @param N the number of steps
 * @param ya the boundary condition at x=a
 * @param yb the boundary condition at x=b
 * @param x array to store x values
 * @param y array to store y values

 * @return Returns k fulfilling g(k) = 0. Function g is hard-coded.  
 * @throws None.
 */
double bisect_g(double k1, double k2, double a, double b, int N, double ya, double yb, double* x, double* y) {

    int imax = 60;
    double tolerance = 1.0e-9; 
    double dx, xmid, rtbis, fl, fmid;

    // initialize
    fl = g(k1, a, b, N, ya, yb, x, y);
    fmid = g(k2, a, b, N, ya, yb, x, y);

    // a and b must bracket the root
    if (fl * fmid > 0) {
        cerr << "Root must be bracketed." << endl;
        return 1;
    }

    // first search direction
    // the invariable of the algorithm is that midpoint search 
    // always proceeds uphill along the function curve
    // rtbis is set to be the x starting point

    if (fl < 0.0) {
        rtbis = a;
        dx = b - a;
    } else {
        rtbis = b;
        dx = a - b;
    }

    cout << "round\t" << "x\t" << "g(x)" << endl;

    // main loop
    for (int i=0; i<imax; ++i) {
        dx *= 0.5;
        xmid = rtbis + dx;
        fmid = g(xmid, a, b, N, ya, yb, x, y);
        // if fmid has not yet climbed over zero when moving uphill,
        // set rtbis as the new x starting point
        if (fmid <= 0.0) rtbis = xmid;
        cout << i << "\t" << xmid << "\t" << fmid << endl;
        // check if root is close enough
        if (abs(fmid) < tolerance) break;
    }
    return xmid;
}

/**
 * @brief Solve the equation y''(x)+y(x)=0 with boundary conditions.
 * @file shootingSolver.cpp
 * @param a Initial value of x
 * @param b Final value of x
 * @param N Number of steps
 * @param y0 Initial value of y at x=a
 * @param y1 Final value of y at x=b
 * @param x Array to store x values (size N+1)
 * @param y Array to store y values (size N+1)
 */
void shootingSolver(double a, double b, int N, double y0, double y1, double* x, double* y) {

    // Initial guesses for the shooting parameter k
    double k1 = 0.0;  // Initial guess for y'(a)
    double k2 = 2.0;  // Second guess for y'(a)

    // Find the correct initial slope using the bisection method
    double k = bisect_g(k1, k2, a, b, N, y0, y1, x, y);

    // Print the found initial slope
    cout << "Found initial slope y'(" << a << ") = " << k << endl;

}