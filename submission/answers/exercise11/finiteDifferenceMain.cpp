#include <iostream>
#include <utility>
#include <iomanip>
#include <Eigen/Core>
#include <Eigen/Eigenvalues>
using Eigen::MatrixXd;

using namespace Eigen;
using namespace std;


// Function declarations
pair<VectorXd, MatrixXd> solveEigenproblem(int N, double h);

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "finiteDifferenceStencil - solve the dimensionless Schrödinger equation using finite differences" << endl << endl;
    cout << "Usage:" << endl;
    cout << "  finiteDifferenceStencil N h" << endl;
    cout << "  finiteDifferenceStencil --help" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl << endl;
    cout << "Arguments:" << endl;
    cout << "  N            number of interior points" << endl;
    cout << "  h            step size" << endl << endl;
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

int main(int argc, char** argv){

    if (argc == 1) { // The first argument is the program name
        cerr << getArgumentCountErrorMessage(argv[0], 2, argc - 1) << endl;
        return 1;
    }
    
    string flag = argv[1];

    if (flag == "--help" || flag == "-h" || flag == "-H") {
        displayHelp();
        return 0;
    } 

    if (argc != 3) {
        cerr << getArgumentCountErrorMessage(argv[0], 2, argc - 1) << endl;
        return 1;
    }
    
    int N = stoi(argv[1]); // Number of interior points
    double h = stod(argv[2]); // Step size

    if (N <= 0 || h <= 0.0) {
        cerr << "Invalid arguments provided." << endl;
        cerr << "N: Number of interior points (positive integer)" << endl;
        cerr << "h: Step size (positive float)" << endl;
        return 1;
    }   

    auto [energies, wavefunctions] = solveEigenproblem(N, h);

    // Print all energies
    cout << "Energies:\n" << setprecision(6) << energies << endl; 
    
    // Print all wave functions
    int n = energies.size();
    cout << "Corresponding wave functions:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Wave function " << (i + 1) << ":\n" << setprecision(6) << wavefunctions.col(i).transpose() << endl;
    }

    return 0;
}