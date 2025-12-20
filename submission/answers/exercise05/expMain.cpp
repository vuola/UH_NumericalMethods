#include <iostream>
#include <string>
#include <cmath>
#include <numbers>
#include <cstdlib>

using namespace std;

double myexp(double x);
double doubleRand();

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "exp - optimized calculation of e^x by reducing the problem" << endl << endl;
    cout << "Usage:" << endl;
    cout << "  exp x" << endl;
    cout << "  exp --help" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl;
    cout << "Arguments:" << endl;
    cout << "  x           power" << endl << endl;
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

// Main function implementing command line 
int main(int argc, char** argv){

    if (argc == 1) { // The first argument is the program name
        double x = doubleRand() * 20 - 10;
        cout << "value of x is " << x << endl;
        cout << "regular exp function: " << exp(x) << endl;
        cout << "mapped exp function: " << myexp(x) << endl;
        return 0;
    }

    if (argc == 2) {
            string flag = argv[1];
            if (flag == "--help" || flag == "-h" || flag == "-H") {
                displayHelp();
                return 0;
            }    

            double x = stod(argv[1]);
            cout << "value of x is " << x << endl;
            cout << "regular exp function: " << exp(x) << endl;
            cout << "mapped exp function: " << myexp(x) << endl;
            return 0;
    }    

    cerr << getArgumentCountErrorMessage(argv[0], 1, argc - 1) << endl;
    return 1;    
 
}