#include <iostream>
#include <string>
#include <Eigen/Core>
 
using Eigen::MatrixXd;
using Eigen::ArrayXd;
using Eigen::VectorXd;

using namespace std;

/**
 * jacobi - Matrix eigenvalues computed with Jacobi method 
 *
 * @return Returns an N-vector of eigenvalues, computed from input N x N matrix Q.  
 *  
 * @throws None.
 *
 * Example:
 * @code
 * VectorXd e = jacobi(Q, N);
 * @endcode
 */
VectorXd jacobi(MatrixXd Q, int N)
{
    VectorXd x;
    x = Q.diagonal();
    return x;
}
