#include <iostream>
#include <utility>
#include <string>
#include <Eigen/Core>

std::pair<double, double> funks(double x);
Eigen::MatrixXd funksRange(double first, double last, int N);

using namespace std;

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "funks - compute a trigonometric and exponent function" << endl;
    cout << "first: (cos(x)-1)/x^2   second: (exp(x)-exp(-x))/2*x" << endl << endl;
    cout << "Usage:" << endl;
    cout << "  funks [flags] <args...>" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl;
    cout << "  --range       compute x and function values in range" << endl << endl;
    cout << "Arguments:" << endl;
    cout << "  x                     variable x of both functions" << endl;
    cout << "  --range xmin xmax N   evaluate functions between xmin, xmax with N points -> [3,N]" << endl;
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

// Main function implementing command line 
int main(int argc, char** argv){

    string flag = argv[1];

    if (flag == "--help" || flag == "-h" || flag == "-H") {
        displayHelp();
        return 0;
    }

    if (flag == "--range" || flag == "-r" || flag == "-R") {
        if (argc != 5) {
            // Wrong number of arguments
            cerr << getArgumentCountErrorMessage(argv[0], 3, argc - 2) << endl;
            return 1;
        }
        double arg2 = stod(argv[2]);
        double arg3 = stod(argv[3]);
        double arg4 = stoi(argv[4]);
        cout << funksRange(arg2, arg3, arg4) << endl;
        return 0;
    }

    if (argc != 2) {  
        // Wrong number of arguments
        cerr << getArgumentCountErrorMessage(argv[0], 1, argc - 1) << endl;
        return 1;    

    }

    // Convert command-line argument to the appropriate type
    double arg1 = stod(argv[1]);
    pair<double, double> result = funks(arg1);
    cout << result.first << " " << result.second << endl;
    return 0;
}
