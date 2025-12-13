#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include "bernstein_polynomial.hpp"

//****************************************************************************80
void bernstein_poly_01 ( int n, double x, std::vector<double> &bern )

//****************************************************************************80
//
//  Purpose:
//
//    BERNSTEIN_POLY_01 evaluates the Bernstein polynomials based in [0,1].
//
//  Discussion:
//
//    The Bernstein polynomials are assumed to be based on [0,1].
//
//    The formula is:
//
//      B(N,I)(X) = [N!/(I!*(N-I)!)] * (1-X)^(N-I) * X^I
//
//  First values:
//
//    B(0,0)(X) = 1
//
//    B(1,0)(X) =      1-X
//    B(1,1)(X) =                X
//
//    B(2,0)(X) =     (1-X)^2
//    B(2,1)(X) = 2 * (1-X)    * X
//    B(2,2)(X) =                X^2
//
//    B(3,0)(X) =     (1-X)^3
//    B(3,1)(X) = 3 * (1-X)^2 * X
//    B(3,2)(X) = 3 * (1-X)   * X^2
//    B(3,3)(X) =               X^3
//
//    B(4,0)(X) =     (1-X)^4
//    B(4,1)(X) = 4 * (1-X)^3 * X
//    B(4,2)(X) = 6 * (1-X)^2 * X^2
//    B(4,3)(X) = 4 * (1-X)   * X^3
//    B(4,4)(X) =               X^4
//
//  Special values:
//
//    B(N,I)(X) has a unique maximum value at X = I/N.
//
//    B(N,I)(X) has an I-fold zero at 0 and and N-I fold zero at 1.
//
//    B(N,I)(1/2) = C(N,K) / 2^N
//
//    For a fixed X and N, the polynomials add up to 1:
//
//      Sum ( 0 <= I <= N ) B(N,I)(X) = 1
//
//  Licensing:
//
//    This code is distributed under the MIT license. 
//
//  Modified:
//
//    29 July 2011
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, int N, the degree of the Bernstein polynomials 
//    to be used.  For any N, there is a set of N+1 Bernstein polynomials,
//    each of degree N, which form a basis for polynomials on [0,1].
//
//    Input, double X, the evaluation point.
//
//    Output, std::vector<double> BERNSTEIN_POLY[N+1], the values of the N+1 
//    Bernstein polynomials at X.
//
{
  if ( n == 0 )
  {
    bern[0] = 1.0;
  }
  else if ( 0 < n )
  {
    bern[0] = 1.0 - x;
    bern[1] = x;
 
    for ( int i = 2; i <= n; i++ )
    {
      bern[i] = x * bern[i-1];
      for ( int j = i - 1; 1 <= j; j-- )
      {
        bern[j] =         x   * bern[j-1] 
                + ( 1.0 - x ) * bern[j];
      }
      bern[0] = ( 1.0 - x ) * bern[0];
    }
  }
}



int main(int argc, char* argv[]) {
    int n, mt;
    double dt, x, y, t;
    std::vector<double> b, xa, ya;
    char *argu;

    if (argc != 3) {
        std::cout << "usage: bezier n dt" << std::endl;
        return 0;
    }

    argu = argv[1];
    n = std::stoi(argu);
    argu = argv[2];
    dt = std::stod(argu);

    n = n - 1;
    b.resize(n + 1);
    xa.resize(n + 1);
    ya.resize(n + 1);

    for (int i = 0; i <= n; i++) {
        std::cin >> xa[i] >> ya[i];
    }

    mt = 1.0 / dt;
    for (int m = 0; m <= mt; m++) {
        t = dt * m;
        x = 0.0;
        y = 0.0;

        bernstein_poly_01(n, t, b);

        for (int i = 0; i <= n; i++) {
            y = y + ya[i] * b[i];
        }

        bernstein_poly_01(n, t, b);

        for (int i = 0; i <= n; i++) {
            x = x + xa[i] * b[i];
        }

        std::cout << x << " " << y << std::endl;
    }

    return 0;
}
