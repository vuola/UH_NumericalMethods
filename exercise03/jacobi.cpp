#include <iostream>
#include <string>
#include <cstdlib>
#include "residual.cpp"
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
 * @brief jacobi - Matrix eigenvalues computed with Jacobi method 
 * @return Returns an N-vector of eigenvalues, computed from input N x N matrix A.  
 *  
 * @throws None.
 *
 * @param A input matrix (N x N), typically coefficients of linear equation
 * @param N row and col dimension of A
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

// double mNorm(int m, VectorXd v);

/**
 * @brief
 * err_propag - Relative error propagation factor of jacobi for testing quality of jacobi algorithm. 
 * 
 * A random symmetric N x N matrix A is used as jacobi input to calculate eigenvalue vector
 * [e_1, ... e_N]. A random single-element perturbation A(i,j) = (1 + dq) * A(i,j) is applied to A and jacobi is 
 * re-run with perturbed A. The output of jacobi changes now by [d e_1, ..., d e_N].  
 * @return  
 * Relative error measured by euclidean vector norms: 
 * || [d e_1, ..., d e_N] || / ( || [e_1, ... , e_N] || * dq )
 * 
 * @throws None.
 * @param N Dimension of (N,N) random matrix 
 * @param dq Relative perturbation: A_perturbed (i,j) = (1 + dq) * A(i,j)
 * 
 **/
double err_propag(int N, double dq) {
    double de_norm;
    double e_norm;
    VectorXd eig;
    MatrixXd A(N,N);
    int randi;
    int randj;

    // random A matrix
    A.setRandom(N, N);

    // random index of perturbed A-element
    srand((unsigned) time(NULL));
    randi = 0 + (rand() % N);
    randj = 0 + (rand() % N);

    // original eigenvalues and their norm
    eig = jacobi(A, N);
    e_norm = mNorm(2,eig);

    // perturbed eigenvalues, norm of difference to originals
    A(randi,randj) *= (1 + dq);
    de_norm = mNorm(2, eig-jacobi(A, N));

    // relative error
    return de_norm / (dq * e_norm);
}