#include <iostream>
#include <string>
#include <Eigen/Core>
 
using Eigen::MatrixXd;
using Eigen::ArrayXd;
using Eigen::VectorXd;

using namespace std;

/**
 * mNorm - norm-m of a vector
 *
 * @return Norm-m of the vector v. The degree of the norm is given as argument
 *         and can have values m = 0,1,2,... where 0 represents the infinite norm.   
 * @throws None.
 *
 * Example:
 * @code
 * double n = mNorm(m, v);
 * @endcode
 */
double mNorm(int m, VectorXd v)
{
    double norm = 0;
    int N = v.size();
    if (m == 0) {
        norm = v.array().abs().maxCoeff();
    } else {
        for(int i=0; i<N; ++i) {
            norm += pow(abs(v(i)),m);
        }
        norm = pow(norm,(1.0/m));
    }
    return norm;
}


/**
 * residual - norm-m of the residual ||Ax-b|| i.e. of the solution of an NxN linear system.
 *
 * @return norm-m of the residual ||Ax-b|| 
 * @throws None.
 *
 * Example:
 * @code
 * double r = residual(N, A, x, b, m);
 * @endcode
 */
double residual(int N, MatrixXd A, VectorXd x, VectorXd b, int m)
{
    VectorXd resv;
    resv = A * x - b;
    return mNorm(m, resv);
}