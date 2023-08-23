#include <iostream>
#include <utility>
#include <string>
#include <cmath>

using namespace std;

/**
 * funks - displays two trigonometric functions 
 * first equation: (cos(x)-1)/x^2   second equation: (exp(x)-exp(-x))/2*x
 * @return a pair of function values: <first equation, second equation>
 * @throws None
 *
 * Example:
 * @code
 * pair<double, double> result = funks(x);
 * @endcode
 */
pair<double, double> funks(double x){

    double left = (cos(x)-1)/pow(x,2);
    double right = (exp(x)-exp(-x))/(2*x);
    
    return make_pair(left, right);
}
