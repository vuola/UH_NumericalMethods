#include <iostream>
#include <string>

using namespace std;

double err_propag(int N, double dq);

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "err_propag - Relative error propagation factor of jacobi with one random delta A(i,j)" << endl << endl;
    cout << "A random symmetric N x N matrix A is used as jacobi input to calculate eigenvalue vector" << endl;
    cout << "[e_1, ... e_N]. A random single-element perturbation A(i,j) = dq * A(i,j) is applied to A" << endl;   
    cout << "and jacobi is re-run with perturbed A. The output of jacobi changes now by [d e_1, ..., d e_N]." << endl << endl; 
    cout << "The output of err_propag is the relative error measured with euclidean vector norms:" << endl; 
    cout << "|| [d e_1, ..., d e_N] || / ( || [e_1, ... , e_N] || * dq )" << endl << endl; 
    cout << "The err_propag function needs to be called many times when forming a sample distribution." << endl << endl;
    cout << "Usage:" << endl;
    cout << "  err_propag N dq" << endl;
    cout << "  err_propag --help" << endl << endl;
    cout << "Flags:" << endl;
    cout << "    --help     display help message" << endl << endl;
    cout << "Arguments:" << endl;
    cout << "         N      dimensions of the random (N x N) matrix A when calling jacobi" << endl;
    cout << "        dq      relative perturbation: A(i,j) = dq * A(i,j)" << endl << endl;
  
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

// Main function implementing command line 
int main(int argc, char** argv) {

    if (argc < 2 || argc > 3) { 
        // Wrong number of arguments
            cerr << getArgumentCountErrorMessage(argv[0], 2, argc - 1) << endl;
            return 1;
    } 

    if (argc == 2) {
        string flag = argv[1];
        if (flag == "--help" || flag == "-h" || flag == "-H") {
            displayHelp();
            return 0;
        }
    }   

    int arg1 = stoi(argv[1]);
    double arg2 = stod(argv[2]);

    cout << "Relative perturbation: " << err_propag(arg1, arg2) << endl; 
}


