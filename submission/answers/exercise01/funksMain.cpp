#include <iostream>
#include <utility>
#include <string>
#include <Eigen/Core>

std::pair<double, double> funks(double x);
std::pair<double, double> funks_Taylor(double x);
std::pair<double, double> funksError(double z, int n);
Eigen::MatrixXd funksRange(double first, double last, int N);

using namespace std;

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "funks - Compute a trigonometric and exponent function" << endl;
    cout << "        and a Taylor series value of both. Also Taylor error is displayed." << endl;
    cout << "        first function: (cos(x)-1)/x^2   second function: (exp(x)-exp(-x))/2*x" << endl << endl;
    cout << "Usage:" << endl;
    cout << "  funks [flags] <args...>" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        Display help message" << endl;
    cout << "  --range       Generate x vector and evaluate functions and Taylor series values in x vector points." << endl;
    cout << "                The output [5,N] matrix has row vectors {x, f1, f1_Taylor, f2, f2_Taylor}' " << endl << endl;
    cout << "Arguments:" << endl;
    cout << "  x                     With scalar x evaluate functions, Taylor series, and closed-form Taylor series errors" << endl;
    cout << "  --range xmin xmax N   Evaluate functions and Taylor series in N x-points between xmin and xmax -> [5,N]" << endl;
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
    pair<double, double> resultF = funks(arg1);
    pair<double, double> resultT = funks_Taylor(arg1);
    pair<double, double> resultE = funksError(arg1, 3);
    cout << "functions:     " << resultF.first << " " << resultF.second << endl;
    cout << "Taylor series: " << resultT.first << " " << resultT.second << endl;
    cout << "Taylor error:  " << resultE.first << " " << resultE.second << endl;
    return 0;
}
