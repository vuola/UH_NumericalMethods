#include <iostream>
#include <utility>
#include <iomanip>
#include <Eigen/Core>
#include <Eigen/Eigenvalues>
using Eigen::MatrixXd;

using namespace Eigen;
using namespace std;

// Declarations
MatrixXd finiteDifferenceStencil(int N, double h);

/**
 * @brief Compute the potential vector V = V0 * (1 - x^2) for a given
 * @brief number of interior points for range [-1, 1]
 * @file finDiffParabolicPotential.cpp
 * @param N Number of interior points
 * @param V0 Strength of the parabolic potential
 * @return Potential vector of size N
 */
VectorXd computeParabolicPotential(int N, double V0) {
    VectorXd V(N);
    double h = 2.0 / (N + 1); // Step size for interval [-1, 1]
    for (int i = 0; i < N; ++i) {
        double x = -1.0 + (i + 1) * h; // Interior points
        V(i) = V0 * (1 - x * x);
    }
    return V;
}


/**
 * @brief Solve the eigenproblem Dψ = -2[E-V(x)]ψ
 * @brief Now the equation becomes [D-2*diag(V)]ψ = -2Eψ
 * @file finDiffParabolicPotential.cpp
 * @param N Number of interior points
 * @param h Step size
 * @param V0 Strength of the parabolic potential
 * @return Energies E and wave functions ψ as a pair
 */
pair<VectorXd, MatrixXd> solveEigenproblem(int N, double h, double V0) {
    // Compute the potential vector
    VectorXd V = computeParabolicPotential(N, V0);

    // Construct the finite difference stencil
    MatrixXd D = finiteDifferenceStencil(N, h);
    // Modify D to include the potential term
    for (int i = 0; i < N; ++i) {
        D(i, i) -= 2.0 * V(i);
    }

    // Solve the eigenvalue problem
    SelfAdjointEigenSolver<MatrixXd> solver(D);
    if (solver.info() != Success) {
        cerr << "Eigenvalue decomposition failed!" << endl;
        exit(1);
    }
    // Return the eigenvalues and eigenvectors
    return {make_pair(solver.eigenvalues() * -0.5, solver.eigenvectors())};
}


/**
 * @brief Lowest value of E given by perturbation theory
 * @brief for parabolic potential V = V0 * (1 - x^2) and range x = [-1, 1]
 * @file finDiffParabolicPotential.cpp
 * @param N Number of interior points
 * @param h Step size
 * @param V0 Strength of the parabolic potential
 */
double perturbationTheoryLowestEnergy(int N, double h, double V0) {
    // E0 and psi0 are obtained with V0 = 0
    auto [E0, psi0] = solveEigenproblem(N, h, 0.0);

    // Compute the potential vector
    VectorXd V = computeParabolicPotential(N, V0);

    // Perturbation theory E = E0 + Integral(-1,1, psi0^2 * V dx) / Integral(-1,1, psi0^2 dx)
    double integral1 = (psi0.array().square() * V.array()).sum() * h;
    double integral2 = psi0.array().square().sum() * h;

    // Compute E0 + integral1 / integral2 using lowest energy state
    return E0[0] + integral1 / integral2;
}