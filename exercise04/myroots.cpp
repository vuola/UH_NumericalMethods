#include <iostream>
#include <string>
#include <cmath>
#include <complex>
#include <Eigen/Core>
#include <Eigen/Eigenvalues>
 
using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::VectorXcd;
using Eigen::EigenSolver;
using namespace std;

/**
 * @brief myroots - find roots of a polynomial P(x)= a0+a1*x+a2*x^2+...+an*x^n  
 * @return Returns N-vector r, vector elements are complex roots of P(x).
 *  
 * @throws None.
 *
 * @param N is one less than the number or terms in polynomial P(x)
 * @param a N+1 vector of general polynomial multipliers. a(N) is multiplier of x^N and a(0) is the constant a0.
 */
VectorXcd myroots(int N, VectorXd a) {

    MatrixXd A(N,N);
    A.setZero(N,N);
    A.bottomLeftCorner(N-1,N-1).setIdentity(N-1,N-1);

    // From general polynomial multipliers create standard "p" multipliers.   
    // pN, the multiplier of x^N, is always 1 and is not stored in companion matrix A.
    for (int i=0; i<N; ++i) {
        A(0,i) = - a(N-1-i)/a(N);
    }

    // Solve eigenvalues of companion matrix A, these are the roots of P(x)
    EigenSolver<MatrixXd> es(A);
    return es.eigenvalues();
}

/**
 * @brief evalP - evaluate polynomial P(x)= a0+a1*x+a2*x^2+...+an*x^n 
 * @return Returns N-vector p, vector elements are values of P(x) at given input points x
 *  
 * @throws None.
 *
 * @param a N+1 vector of general polynomial multipliers. a(N) is multiplier of x^N and a(0) is the constant a0.
 * @param x points in where to evaluate polynomial P(x), x can have complex values.
 */
VectorXcd evalP(VectorXd a, VectorXcd X) {

    int K = size(a);
    int M = size(X);
    VectorXcd P;
    std::complex<double> xpow; 

    for (int i = 0; i < M; ++i) {
        P(i) = 0;
        for (int j = 0; j < K; ++j) {
            xpow = std::pow(X(i),j);
            P(i) += a(j)*xpow;
        }
    }
    return P;
}

