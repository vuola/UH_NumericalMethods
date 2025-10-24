#include <iostream>
#include <utility>
#include <iomanip>
#include <Eigen/Core>
#include <Eigen/Eigenvalues>

#define DEBUG_OUTPUT 0

using Eigen::MatrixXd;

using namespace Eigen;
using namespace std;


// Function declarations
pair<VectorXd, MatrixXd> solveEigenproblem(int N, double h, double V0);
double perturbationTheoryLowestEnergy(int N, double h, double V0);

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "finDiffParabolicPotential - Solve Dψ = -2[E-V(x)]ψ using finite differences." << endl << "Potential function V = V0 * (1 - x^2)" << endl << endl;
    cout << "Usage:" << endl;
    cout << "  finDiffParabolicPotential N h V0" << endl;
    cout << "  finDiffParabolicPotential --help" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl << endl;
    cout << "Arguments:" << endl;
    cout << "  N            number of interior points" << endl;
    cout << "  h            step size" << endl;
    cout << "  V0           strength of the parabolic potential" << endl << endl;
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

int main(int argc, char** argv){

    if (argc == 1) { // The first argument is the program name
        cerr << getArgumentCountErrorMessage(argv[0], 3, argc - 1) << endl;
        return 1;
    }
    
    string flag = argv[1];

    if (flag == "--help" || flag == "-h" || flag == "-H") {
        displayHelp();
        return 0;
    } 

    if (argc != 4) {
        cerr << getArgumentCountErrorMessage(argv[0], 3, argc - 1) << endl;
        return 1;
    }
    
    int N = stoi(argv[1]); // Number of interior points
    double h = stod(argv[2]); // Step size
    double V0 = stod(argv[3]); // Strength of the parabolic potential

    if (N <= 0 || h <= 0.0 || V0 < 0.0) {
        cerr << "Invalid arguments provided." << endl;
        cerr << "N: Number of interior points (positive integer)" << endl;
        cerr << "h: Step size (positive float)" << endl;
        cerr << "V0: Strength of the parabolic potential (non-negative float)" << endl;
        return 1;
    }   

    auto [energies, wavefunctions] = solveEigenproblem(N, h, V0);
    double theoreticalLowestE = perturbationTheoryLowestEnergy(N, h, V0);

    // Print all energies
    if (DEBUG_OUTPUT) {
        cout << "All energies:\n" << setprecision(6) << energies.transpose() << endl;
    }
    cout << "Lowest energy:\n" << setprecision(6) << energies[N-1] << endl;
    
    cout << "Lowest energy from perturbation theory: " << setprecision(6) << theoreticalLowestE << endl;
    
    // Print all wave functions
    if (DEBUG_OUTPUT) {
        int n = energies.size();
        cout << "Corresponding wave functions:\n";
        for (int i = 0; i < n; ++i) {
            cout << "Wave function " << (i + 1) << ":\n" << setprecision(6) << wavefunctions.col(i).transpose() << endl;
        }
    }

    return 0;
}