#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * harmonic - sum of series with general term (1/k)
 *
 * @param N Number of terms in the series
 * @return Sum of (1/k) where k = { 1, ..., N }
 * @throws None.
 *
 * Example:
 * @code
 * float sum = harmonic(N);
 * @endcode
 */
float harmonic(int N){

    float sum=0;
    for (int i=1; i<=N; i++){
        sum += 1.0/i;
    }
    return sum; 
}

// Function to display help message
void displayHelp(string funct) {
    cout << endl;
    cout << "Usage: " << funct << " [flags] <args...>" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help   display help message" << endl << endl;
    cout << "Arguments:" << endl;
    cout << "  N        calculate sum of (1/k) where k = { 1, ..., N }" << endl << endl;
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

// Main function implementing command line 
int main(int argc, char** argv){

    if (argc == 1) { // The first argument is the program name
        cerr << "Error: No arguments provided. Try " << argv[0] << " --help" << endl;
        return 1;
    }

    string flag = argv[1];

    if (flag == "--help" || flag == "-h" || flag == "-H") {
        displayHelp(argv[0]);
        return 0;
    }

    if (argc != 2) {  
        cerr << getArgumentCountErrorMessage(argv[0], 1, argc - 1) << endl;
        return 1;    
    }

    // Convert command-line arguments to the appropriate types
    int arg1 = stoi(argv[1]);

    cout << harmonic(arg1) << endl;

}
