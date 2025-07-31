#include <iostream>
#include <string>
#include <vector>

using namespace std;

double golden(double xa, double xc);

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "golden - find the minimum of a function using the golden section search" << endl << endl;
    cout << "Usage:" << endl;
    cout << "  golden xa xc" << endl;
    cout << "  golden --help" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl;
    cout << "Arguments:" << endl;
    cout << "  xa           left endpoint of the interval" << endl;
    cout << "  xc           right endpoint of the interval" << endl << endl;
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

// Main function implementing command line 
int main(int argc, char** argv){

    if (argc == 1) { // The first argument is the program name
        cerr << getArgumentCountErrorMessage(argv[0], 1, argc - 1) << endl;
        return 1;
    }

    string flag = argv[1];

    if (flag == "--help" || flag == "-h" || flag == "-H") {
        displayHelp();
        return 0;
    }

    if (argc == 2) {
            double arg1 = stod(argv[1]);
            double arg2 = stod(argv[2]);
            cout << golden(arg1, arg2) << endl;
            return 0;
    }

    cerr << getArgumentCountErrorMessage(argv[0], 2, argc - 1) << endl;
    return 1;    
 
}