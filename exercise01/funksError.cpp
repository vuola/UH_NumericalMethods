#include <iostream>
#include <utility>
#include <string>
#include <cmath>

using namespace std;

/**
 * funksError - displays Taylor n-series errors of two functions 
 * first function: (cos(x)-1)/x^2   second function: (exp(x)-exp(-x))/2*x
 * @return a pair of error values: <first_function, second_function>
 * @throws None
 *
 * Example:
 * @code
 * pair<double, double> result = funksError(x, n);
 * @endcode
 */
pair<double, double> funksError(double z, int n){

    double first_function, second_function = 0.0;

    if (n == 1) {
        first_function = (-z*sin(z)-2.0*cos(z)+2.0)/pow(z,2);
        second_function = exp(-z)*(exp(2*z)*(z-1)+z+1)/(2*z);    
    } else if (n == 2) {
        first_function = (-(pow(z,2)-6)*cos(z)+4.0*z*sin(z)-6.0)/(2*pow(z,2));
        second_function = exp(-z)*(-pow(z,2)+exp(2*z)*(pow(z,2)-2*z+2)-2*z-2)/(4*z);    
    } else if (n == 3) {
        first_function = (z*(pow(z,2)-18)*sin(z)+6*(pow(z,2)-4)*cos(z)+24)/(6*pow(z,2));
        second_function = exp(-z)*(pow(z,3)+3*pow(z,2)+exp(2*z)*(pow(z,3)-3*pow(z,2)+6*z-6)+6*z+6)/(12*z);    
    } else {
        cerr << "Taylor n can be only 1, 2 or 3" << endl;
    }
    return make_pair(first_function, second_function);
}

