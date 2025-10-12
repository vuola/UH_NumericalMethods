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

int main(int argc, char** argv){

    int N = stoi(argv[1]); // Number of interior points
    double h = stod(argv[2]); // Step size

    if (argc != 3 || N <= 0 || h <= 0.0) {
        cerr << "Usage: " << argv[0] << " <N> <h>" << endl;
        cerr << "N: Number of interior points (positive integer)" << endl;
        cerr << "h: Step size (positive float)" << endl;
        return 1;
    }   

    auto [energies, wavefunctions] = solveEigenproblem(N, h);

    cout << "Energies:\n" << setprecision(6) << energies << endl; 
    
    // Print all energies

    int n = energies.size();
    cout << "Corresponding wave functions:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Wave function " << (i + 1) << ":\n" << setprecision(6) << wavefunctions.col(i).transpose() << endl;
    }

    return 0;
}