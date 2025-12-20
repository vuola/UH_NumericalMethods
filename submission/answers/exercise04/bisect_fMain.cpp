#include <iostream>
#include <string>

using namespace std;

double bisect_f(double a, double b);

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "bisect_f - find solution to f(x) = 0 between x = [a, ..., b]" << endl;
    cout << "Returns x fulfilling f(x) = 0. Function f is hard-coded." << endl << endl;
    cout << "Usage:" << endl;
    cout << "  bisect a b" << endl;
    cout << "  bisect --help" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl << endl;
    cout << "Arguments:" << endl;
    cout << "       a        left edge (x-value) of search bracket" << endl;
    cout << "       b        right edge (x-value) of search bracket" << endl;
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
        }
    }   

    double a = stod(argv[1]);
    double b = stod(argv[2]);

    double out = bisect_f(a,b);
    cout << "Final root: " << out << endl;  
}