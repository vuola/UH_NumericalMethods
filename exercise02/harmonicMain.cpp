#include <iostream>
#include <string>
#include <vector>

using namespace std;

float harmonic_kahan(int);

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "harmonic_kahan - sum of series with general term (1/k) with Kahan compensation" << endl << endl;
    cout << "Usage:" << endl;
    cout << "  harmonic_kahan N" << endl;
    cout << "  harmonic_kahan --help" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl;
    cout << "Arguments:" << endl;
    cout << "  N             number of terms in sum" << endl << endl;
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
            int arg1 = stoi(argv[1]);
            cout << harmonic_kahan(arg1) << endl;
            return 0;
    }

    cerr << getArgumentCountErrorMessage(argv[0], 1, argc - 1) << endl;
    return 1;    
 
}
