#include <iostream>
#include <string>
#include <vector>

using namespace std;

float harmonic();
float harmonic_bunch(int);

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "harmonic - sum of series with general term (1/k)" << endl << endl;
    cout << "Usage:" << endl;
    cout << "  harmonic" << endl;
    cout << "  harmonic [flags] <args...>" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl;
    cout << "  --bunch <arg> compute in groups of N terms, takes N as argument" << endl << endl;
    cout << "Arguments:" << endl;
    cout << "  N             number of terms in group" << endl << endl;
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

// Main function implementing command line 
int main(int argc, char** argv){

    if (argc == 1) { // The first argument is the program name
        cout << harmonic() << endl;
        return 0;
    }

    string flag = argv[1];

    if (flag == "--help" || flag == "-h" || flag == "-H") {
        displayHelp();
        return 0;
    }

    if (flag == "--bunch" || flag == "-b" || flag == "-B") {
        if (argc != 3) {  
            // Argument N for --bunch mode is mssing
            cerr << getArgumentCountErrorMessage(argv[0], 1, argc - 2) << endl;
            return 1;    
        } else {
            // Convert command-line argument to the appropriate type
            int arg1 = stoi(argv[2]);
            cout << harmonic_bunch(arg1) << endl;
            return 0;
        }
    }

    cerr << getArgumentCountErrorMessage(argv[0], 0, argc - 1) << endl;
    return 1;    
 
}
