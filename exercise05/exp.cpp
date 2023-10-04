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

double doubleRand() {
    srand((unsigned) time(NULL));
    return double(rand()) / (double(RAND_MAX) + 1.0);
}

int main() {
    double x = doubleRand() * 20 - 10;
    cout << "value of x is " << x << endl;
    cout << "regular exp function: " << exp(x) << endl;
    cout << "mapped exp function: " << myexp(x) << endl;
}