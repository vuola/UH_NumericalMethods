#include <iostream>
#include <string>
#include <Eigen/Core>
 
using Eigen::MatrixXd;
using Eigen::VectorXd;

using namespace std;

/**
 *
 *  Subroutines required by function 'jacobi'
 * 
 */

// Suboutine for computing Variable C
inline double C_(MatrixXd &A, int &p, int &q) {
    return (A(p,p)-A(q,q))/sqrt(pow(A(p,p)-A(q,q),2)+4*pow(A(p,q),2));
}

// Subroutine for sign multiplier
inline int sgn(double &v) {
  return ( ( (v) < 0 )  ?  -1   : ( (v) > 0 ) );
}

// Subroutine for computing variables c and s
inline pair<double, double> cs_(double &C, MatrixXd &A, int &p, int &q) {
    pair<double, double> out;
    // compute c
    out.first = sqrt((1+C)/2);
    // compute s
    out.second = sgn(A(p,q))*sqrt((1-C)/2);
    return out;
}

// Suboutine for constructing matrix Q
inline MatrixXd Q_(int N, pair<double, double> &cs, int &p, int &q) {
    MatrixXd Q = MatrixXd::Identity(N,N);
    Q(p,p) = cs.first;
    Q(q,q) = cs.first;
    Q(p,q) = -cs.second;
    Q(q,p) = cs.second;
    return Q;
}

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
VectorXd jacobi(MatrixXd A, int N)
{
    VectorXd x;
    MatrixXd B(N,N);
    MatrixXd Bwip(N,N);
    double C;
    pair<double, double> cs;
    MatrixXd Q(N,N);
    int imax = 2 * N;

    B = A;
    for (int i=0; i<imax; ++i) {
        for (int p=0; p<N-1; ++p) {
            for (int q=p+1; q<N; ++q) {
                // compute variable C
                C = C_(B,p,q);
                // compute variables c and s
                cs = cs_(C,B,p,q);
                // construct Q
                Q = Q_(N,cs,p,q);
                // transformation
                Bwip = B * Q;
                Q.transposeInPlace();
                B = Q * Bwip;
            }
        }
    }
    x = B.diagonal();
    return x;
}
