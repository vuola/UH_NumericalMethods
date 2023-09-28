#include <iostream>
#include <string>
#include <cmath>
#include <numbers>

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

int main() {
    double x = 2;
    cout << "value of x is " << x << endl;
    cout << "regular exponential: " << exp(x) << endl;
    cout << "custom exponential: " << myexp(x) << endl;
}