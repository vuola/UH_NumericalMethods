#include <iostream>
#include <string>

using namespace std;

double newton_g(double x0, double B);

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "newton_g - use Newton method to find solution to g(x) = 0 starting from x0" << endl;
    cout << "Returns x fulfilling g(x) = 0. Functions g and g' are hard-coded." << endl << endl;
    cout << "Usage:" << endl;
    cout << "  newton_g x0 B" << endl;
    cout << "  newton_g --help" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl << endl;
    cout << "Arguments:" << endl;
    cout << "       x0       starting x-value for search" << endl;
    cout << "       B        constant used in g(x)" << endl;
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

// Main function implementing command line 
int main(int argc, char** argv) {

    if (argc == 1 || argc > 3) { 
        // Wrong number of arguments
            cerr << getArgumentCountErrorMessage(argv[0], 2, argc - 1) << endl;
        return 1;
    } 
    
    if (argc == 2) {
        string flag = argv[1];
        if (flag == "--help" || flag == "-h" || flag == "-H") {
            displayHelp();
            return 0;
        } else {
            cerr << getArgumentCountErrorMessage(argv[0], 2, argc - 1) << endl;
        }
    }   

    double x0 = stod(argv[1]);
    double B = stod(argv[2]);

    double out = newton_g(x0, B);
    cout << "Final root: " << out << endl;  
}