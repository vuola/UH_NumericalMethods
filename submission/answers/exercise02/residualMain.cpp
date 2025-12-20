#include <iostream>
#include <string>
#include <Eigen/Core>

using Eigen::MatrixXd;
using Eigen::ArrayXd;
using Eigen::VectorXd;

using namespace std;

double residual(int, MatrixXd, VectorXd, VectorXd, int);

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "residual - norm-m of the residual ||Ax-b|| i.e. of the solution of an N x N linear system." << endl << endl;
    cout << "Usage:" << endl;
    cout << "  residual m < filename" << endl;
    cout << "  residual --help" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl << endl;
    cout << "Arguments:" << endl;
    cout << "         m      degree of the norm 0,1,2,... where 0 represents infinite norm" << endl;
    cout << "  filename      file containing input paraneters N, A, b, x where:" << endl << endl;
    cout << "Arguments within the file:" << endl;
    cout << "         N      the dimension of the linear system (both row and col)" << endl;
    cout << "         A      (N x N) coefficient matrix " << endl;
    cout << "         b      constant vector (N x 1)" << endl;
    cout << "         x      solution vector (N x 1)" << endl << endl;
    cout << "A sample layout of the input file produced by executable ex2_p3:" << endl << endl;
    cout << "N" << endl;
    cout << "  6" << endl;
    cout << "A" << endl;
    cout << "  0.61611086    0.7106747   0.32931846   0.51194823   0.25304845   0.54417247" << endl; 
    cout << "  0.03563731   0.08815959   0.30034593   0.14795998   0.46325326   0.27647871" << endl; 
    cout << "  0.28538886   0.71970248   0.50220811   0.61753166   0.96837115   0.87984169" << endl; 
    cout << "  0.37600851   0.74768132   0.44811806   0.17185755   0.64607608   0.11992062" << endl; 
    cout << "  0.32336015   0.29026943   0.00099506   0.19949169    0.2208458    0.9813996" << endl; 
    cout << "  0.97817445   0.31981957   0.94624835   0.63531208   0.53851491   0.72695738" << endl; 
    cout << "b" << endl;
    cout << "  0.66863006   0.94118035    0.7253744   0.54309487   0.21732061    0.4329184" << endl; 
    cout << "x" << endl;
    cout << "  -22.413899    12.990382    29.555568   -9.3848441   -21.079137    10.385575" << endl << endl; 
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

// Main function implementing command line 
int main(int argc, char** argv){

    if (argc > 2) { 
        // Wrong number of arguments
            cerr << getArgumentCountErrorMessage(argv[0], 1, argc - 1) << endl;
        return 1;
    }

    string flag = argv[1];

    if (flag == "--help" || flag == "-h" || flag == "-H") {
        displayHelp();
        return 0;
    } else {

        int m = stoi(argv[1]);

        int N;
        string line;

        // Read N into variable
        while (cin >> line) { if (line == "N") break; }
        cin >> N;

        // Read A into an Eigen Matrix
        while (cin >> line) { if (line == "A") break; }
        MatrixXd A(N, N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> A(i, j);
            }
        }

        // Read b into an Eigen Vector
        while (cin >> line) { if (line == "b") break; }
        VectorXd b(N);
        for (int i = 0; i < N; ++i) {
            cin >> b(i);
        }

        // Read x into an Eigen Vector
        while (cin >> line) { if (line == "x") break; }
        VectorXd x(N);
        for (int i = 0; i < N; ++i) {
            cin >> x(i);
        }

        // Print the variables for verification
        // cout << "N:" << endl << N << endl;
        // cout << "A:" << endl << A << endl;
        // cout << "b:" << endl << b << endl;
        // cout << "x:" << endl << x << endl;

        cout <<  "Residual:" << endl << residual(N, A, x, b, m) << endl;  
    }
}

