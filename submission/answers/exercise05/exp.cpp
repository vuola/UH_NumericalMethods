#include <iostream>
#include <string>
#include <cmath>
#include <numbers>
#include <cstdlib>

using namespace std;



/**
 * @brief myexp - solve f(x) = e^x using the periodicity of exponential
 * @return Returns e^x
 *  
 * @throws None.
 *
 * @param x function parameter
 */
double myexp(double x) {

    double x_mapped, l2;
    int n;

    l2 = log(2);
    n = round(x/l2);
    x_mapped = x - n * l2;
    return exp(x_mapped) * pow(2,n);  
}


/**
 * @brief doubleRand - generate a double-precision random number 0.0 ,..., 1.0
 * @brief              the output can be scaled and used as input x for exp(x)
 * @return Returns the random number 
 * @throws None.
 */
double doubleRand() {
    srand((unsigned) time(NULL));
    return double(rand()) / (double(RAND_MAX) + 1.0);
}
