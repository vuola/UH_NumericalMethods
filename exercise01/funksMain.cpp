#include <iostream>
#include <utility>
#include <string>
#include <Eigen/Core>

std::pair<double, double> funks(double x);
std::pair<double, double> funks_Taylor(double x);
Eigen::MatrixXd funksRange(double first, double last, int N);

using namespace std;

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "funks - compute a trigonometric and exponent function" << endl;
    cout << "        and a Taylor series value of both." << endl;
    cout << "        first function: (cos(x)-1)/x^2   second function: (exp(x)-exp(-x))/2*x" << endl << endl;
    cout << "Usage:" << endl;
    cout << "  funks [flags] <args...>" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl;
    cout << "  --range       generate x vector and corresponding function and Taylor series values." << endl;
    cout << "                The output order as row vectors is [x, f1, f1_Taylor, f2, f2_Taylor]' " << endl << endl;
    cout << "Arguments:" << endl;
    cout << "  x                     single evaluation point x" << endl;
    cout << "  --range xmin xmax N   evaluate functions and Taylor series between xmin, xmax with N points -> [5,N]" << endl;
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
    cout << "functions:     " << resultF.first << " " << resultF.second << endl;
    cout << "Taylor series: " << resultT.first << " " << resultT.second << endl;
    return 0;
}
