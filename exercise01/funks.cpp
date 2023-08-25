#include <iostream>
#include <utility>
#include <string>
#include <cmath>

using namespace std;

/**
 * funks - displays a trigonometric and an exponential function 
 * first function: (cos(x)-1)/x^2   second function: (exp(x)-exp(-x))/2*x
 * @return a pair of function values: <first_function, second_function>
 * @throws None
 *
 * Example:
 * @code
 * pair<double, double> result = funks(x);
 * @endcode
 */
pair<double, double> funks(double x){

    double first_function = (cos(x)-1)/pow(x,2);
    double second_function = (exp(x)-exp(-x))/(2*x);
    
    return make_pair(first_function, second_function);
}

/**
 * factorial - calculates factorial of argument
 * @return factorial n! = n(n-1)(n-2)... where 0! = 1! = 1
 * @throws None 
 *
 * Example:
 * @code
 * unsigned long long result = factorial(n);
 * @endcode
 */
unsigned long long factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

/**
 * funks_Taylor - displays Taylor series of functions in funks(x) 
 * first function: (cos(x)-1)/x^2   second function: (exp(x)-exp(-x))/2*x
 * @return a pair of function values: <first_function, second_function>
 * @throws None
 *
 * Example:
 * @code
 * pair<double, double> result = funks_Taylor(x);
 * @endcode
 */

/* Order of Taylor series */
const int N = 3;

pair<double, double> funks_Taylor(double x) {

    /* Function 1: trigonometric function */

    /* term n = 0 */
    double first_function = -0.5;

    /* terms n = 1...N-1 */
    for (int n=1; n<N; ++n) {
        first_function +=  -pow(-1.0, n) * pow(x, 2.0*n) / factorial(2*(1+n));
    }

    /* Function 2: exponential function */

    /* term n = 0 */
    double second_function = 1.0;

    /* terms n = 1...N-1 */
    for (int n=1; n<N; ++n) {
        second_function += pow(x, 2.0*n) / factorial(2*n+1);
    }
    
    return make_pair(first_function, second_function);
}
