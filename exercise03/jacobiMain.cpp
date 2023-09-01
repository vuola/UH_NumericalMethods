#include <iostream>
#include <string>
#include <Eigen/Core>

using Eigen::MatrixXd;
using Eigen::ArrayXd;
using Eigen::VectorXd;

using namespace std;

VectorXd jacobi(MatrixXd, int);

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "jacobi - Matrix eigenvalues computed with Jacobi method " << endl << endl;
    cout << "Usage:" << endl;
    cout << "  jacobi < filename" << endl;
    cout << "  jacobi --help" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl << endl;
    cout << "Arguments:" << endl;
    cout << "  filename      file containing input data:" << endl << endl;
    cout << "Arguments within the file:" << endl;
    cout << "         N      the dimension of the input matrix (both row and col)" << endl;
    cout << "         Q      (N x N) input matrix " << endl << endl;
    cout << "A sample layout of the input file:" << endl << endl;
    cout << "N" << endl;
    cout << "  6" << endl;
    cout << "Q" << endl;
    cout << "  0.61611086    0.7106747   0.32931846   0.51194823   0.25304845   0.54417247" << endl; 
    cout << "  0.03563731   0.08815959   0.30034593   0.14795998   0.46325326   0.27647871" << endl; 
    cout << "  0.28538886   0.71970248   0.50220811   0.61753166   0.96837115   0.87984169" << endl; 
    cout << "  0.37600851   0.74768132   0.44811806   0.17185755   0.64607608   0.11992062" << endl; 
    cout << "  0.32336015   0.29026943   0.00099506   0.19949169    0.2208458    0.9813996" << endl; 
    cout << "  0.97817445   0.31981957   0.94624835   0.63531208   0.53851491   0.72695738" << endl; 
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

// Main function implementing command line 
int main(int argc, char** argv) {

    if (argc > 2) { 
        // Wrong number of arguments
            cerr << getArgumentCountErrorMessage(argv[0], 1, argc - 1) << endl;
        return 1;
    } 
    
    if (argc == 2) {
        string flag = argv[1];
        if (flag == "--help" || flag == "-h" || flag == "-H") {
            displayHelp();
            return 0;
        }
    }   

    int N;
    string line;

    // Read N into variable
    while (cin >> line) { if (line == "N") break; }
    cin >> N;

    // Read Q into an Eigen Matrix
    while (cin >> line) { if (line == "Q") break; }
    MatrixXd Q(N, N);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> Q(i, j);
        }
    }

    // Print the variables for verification
    // cout << "N:" << endl << N << endl;
    cout << "Q:" << endl << Q << endl;

    cout <<  "Eigenvalues:" << endl << jacobi(Q, N) << endl;  
}