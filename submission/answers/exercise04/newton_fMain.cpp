#include <iostream>
#include <string>

using namespace std;

double newton_f(double x0);

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "newton_f - use Newton method to find solution to f(x) = 0 starting from x0" << endl;
    cout << "Returns x fulfilling f(x) = 0. Functions f and f' are hard-coded." << endl << endl;
    cout << "Usage:" << endl;
    cout << "  newton_f x0" << endl;
    cout << "  newton_f --help" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl << endl;
    cout << "Arguments:" << endl;
    cout << "       x0       starting x-value for search" << endl;
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

// Main function implementing command line 
int main(int argc, char** argv) {

    if (argc == 1 || argc > 2) { 
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

    double x0 = stod(argv[1]);

    double out = newton_f(x0);
    cout << "Final root: " << out << endl;  
}