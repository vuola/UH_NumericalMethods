#include <iostream>
#include <utility>
#include <string>
#include <cmath>

using namespace std;

/**
 * @brief
 * funksError - displays Taylor n-series errors of functions (cos(z)-1)/z^2 
 * and (exp(z)-exp(-z))/2*z
 * @return a pair of error values: <err_first_function, err_second_function>
 * @throws None
 *
 * @param z input variable
 * @param n degree of Taylor series, values 1,2, and 3 allowed
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

