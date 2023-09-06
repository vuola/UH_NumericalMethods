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
        if (abs(fmid) < 1.0e-9) break;
    }
    return xmid;
}

/**
 * @brief
 * newton_f - use Newton method to find solution to f(x) = 0 starting from x0 
 * @return  
 * Returns x that fulfilling f(x) = 0. Function f is hard-coded. 
 * @throws None.
 * @param x0 starting x-value for search 
 * 
 **/
double newton_f(double x0) {
    return f(x0);
}