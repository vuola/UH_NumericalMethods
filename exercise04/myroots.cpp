#include <iostream>
#include <string>
#include <cmath>
#include <numbers>
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

int main() {
    VectorXd a(4);
    a(0) = 1;
    a(1) = 2;
    a(2) = 3;
    a(3) = 4;
    cout << myroots(3, a) << endl;
    return 0;
}
