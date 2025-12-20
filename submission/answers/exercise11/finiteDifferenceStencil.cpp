#include <iostream>
#include <utility>
#include <iomanip>
#include <Eigen/Core>
#include <Eigen/Eigenvalues>
using Eigen::MatrixXd;

using namespace Eigen;
using namespace std;

/**
 * @brief Compute the three-point finite difference matrix
 * @brief for dimensionless Schrödinger equation d²ψ/dx² + 2Eψ = 0
 * @file finiteDifferenceStencil.cpp
 * @param N Number of interior points
 * @param h Step size
 * @return Finite difference matrix of size NxN
 */
MatrixXd finiteDifferenceStencil(int N, double h) {
    MatrixXd A = MatrixXd::Zero(N, N);
    for (int i = 0; i < N; ++i) {
        A(i, i) = -2.0 / (h * h);
        if (i > 0) A(i, i - 1) = 1.0 / (h * h);
        if (i < N - 1) A(i, i + 1) = 1.0 / (h * h);
    }
    return A;
}


/**
 * @brief Solve the eigenproblem Dψ = -2Eψ
 * @file finiteDifferenceStencil.cpp
 * @param N Number of interior points
 * @param h Step size
 * @return Energies E and wave functions ψ as a pair
 */
pair<VectorXd, MatrixXd> solveEigenproblem(int N, double h) {
    MatrixXd D = finiteDifferenceStencil(N, h);
    SelfAdjointEigenSolver<MatrixXd> solver(D);
    if (solver.info() != Success) {
        cerr << "Eigenvalue computation did not converge." << endl;
        exit(1);
    }
    return {solver.eigenvalues() * -0.5, solver.eigenvectors()};
}

