#include <iostream>
#include <string>
#include <cmath>
#include <numbers>
 
using namespace std;
using namespace std::numbers;


// Hard-coded function for bisect_f and newton_f
inline double f(double x) {
    return sin(3*pi*pow(x,3)/(pow(x,2)-1))+0.5;
}

// Hard-coded f derivative for newton_f
inline double df(double x) {
    double x2 = pow(x,2);
    double x3 = pow(x,3);
    double term1 = cos(3*pi*x3/(x2-1));
    double term2 = (3*pi*x2*(x2-3))/(pow(x2-1,2));
    return term1 * term2;
}

// Hard-coded function for newton_g
inline double g(double x, double B) {
    return (x + exp(-B * pow(x,2)) * cos(x));
}

// Hard-coded g derivative for newton_g
inline double dg(double x, double B) {
    return (1 - exp(-B * pow(x,2)) * (2*B*x*cos(x)+sin(x)));
}



/**
 * @brief bisect_f - find solution to f(x) = 0 between x = [a, ..., b] 
 * @return Returns x fulfilling f(x) = 0. Function f is hard-coded.  
 *  
 * @throws None.
 *
 * @param a left edge (x-value) of search bracket
 * @param b right edge (x-value) of search bracket
 */
double bisect_f(double a, double b) {

    int imax = 60;
    double tolerance = 1.0e-9; 
    double dx, xmid, rtbis, fl, fmid;

    // initialize
    fl = f(a);
    fmid = f(b);

    // a and b must bracket the root
    if (fl * fmid > 0) {
        cerr << "Root must be bracketed." << endl;
        return 1;
    }

    // first search direction
    if (fl < 0.0) {
        rtbis = a;
        dx = b - a;
    } else {
        rtbis = b;
        dx = a - b;
    }

    cout << "round\t" << "x\t" << "f(x)" << endl;

    // main loop
    for (int i=0; i<imax; ++i) {
        dx *= 0.5;
        xmid = rtbis + dx;
        fmid = f(xmid);
        if (fmid <= 0.0) rtbis = xmid;
        cout << i << "\t" << xmid << "\t" << fmid << endl;
        // check if root is close enough
        if (abs(fmid) < tolerance) break;
    }
    return xmid;
}

/**
 * @brief
 * newton_f - use Newton method to find solution to f(x) = 0 starting from x0 
 * @return  
 * Returns x fulfilling f(x) = 0. Function f is hard-coded. 
 * @throws None.
 * @param x0 starting x-value for search 
 * 
 **/
double newton_f(double x0) {

    int imax = 60;
    double tolerance = 1.0e-9; 
    double fmid;

    // initialize
    double xmid = x0;

    cout << "round\t" << "x\t\t" << "f(x)" << endl;

    // main loop       
    for (int i=0; i<imax; ++i) {
        fmid = f(xmid);
        cout << i << "\t" << xmid << "\t" << fmid << endl;
        xmid = xmid - (fmid / df(xmid));
        // check if root is close enough
        if (abs(fmid) < tolerance) break;
    }
    return xmid;
}

/**
 * @brief
 * newton_g - use Newton method to find solution to g(x) = 0 starting from x0 
 * @return  
 * Returns x fulfilling g(x) = 0. Functions g and g' are hard-coded. 
 * @throws None.
 * @param x0 starting x-value for search 
 * @param B constant used in g(x)
 **/
double newton_g(double x0, double B) {

    int imax = 60;
    double tolerance = 1.0e-9; 
    double fmid;

    // initialize
    double xmid = x0;

    cout << "round\t" << "x\t\t" << "g(x)\t\t" << "g'(x)" << endl;

    // main loop       
    for (int i=0; i<imax; ++i) {
        fmid = g(xmid, B);
        cout << i << "\t" << xmid << "\t" << fmid << "\t" << dg(xmid, B) << endl;
        xmid = xmid - (fmid / dg(xmid, B));
        // check if root is close enough
        if (abs(fmid) < tolerance) break;
    }
    return xmid;
}