#include <iostream>
#include <string>
#include <cmath>

using namespace std;

/**
 * funks - displays two trigonometric functions 
 * first equation: (cos(x)-1)/x^2   second equation: (exp(x)-exp(-x))/2*x
 * @return None
 * @throws None
 *
 * Example:
 * @code
 * funks(x);
 * @endcode
 */
void funks(double x){

    double leftside = (cos(x)-1)/pow(x,2);
    double rightside = (exp(x)-exp(-x))/(2*x);
    
    cout << leftside << " " << rightside << endl;
}

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "funks - compute two trigonometric functions" << endl;
    cout << "first: (cos(x)-1)/x^2   second: (exp(x)-exp(-x))/2*x" << endl << endl;
    cout << "Usage:" << endl;
    cout << "  funks [flags] <args...>" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl;
    cout << "Arguments:" << endl;
    cout << "  x             variable of both functions" << endl << endl;
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

// Main function implementing command line 
int main(int argc, char** argv){

    if (argc != 2) {  
        // Wrong number of arguments
        cerr << getArgumentCountErrorMessage(argv[0], 1, argc - 1) << endl;
        return 1;    

    }
    string flag = argv[1];

    if (flag == "--help" || flag == "-h" || flag == "-H") {
        displayHelp();
        return 0;
    }

    // Convert command-line argument to the appropriate type
    double arg1 = stod(argv[1]);
    funks(arg1);
    return 0;
}
