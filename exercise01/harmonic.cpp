#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * harmonic - sum of series with general term (1/k)
 *
 * @return Sum of (1/k) where k = { 1, ..., Nmax }, stops summing when float(1/k) == 0
 * @throws None.
 *
 * Example:
 * @code
 * float sum = harmonic;
 * @endcode
 */
float harmonic(){

    float sum=0;
    float previous_sum=0;
    int Nmax = 10000000;

    for (int i=1; i<=Nmax; i++){
        previous_sum = sum;
        sum += 1.0/i;

        if (previous_sum == sum){
            cout << "float resolution limit at iteration " << i << endl;
            break;
        } 
    }

    return sum;
}

/**
 * harmonic_bunch - sum of series with general term (1/k), terms summed in batches
 *
 * @param N Number of terms in a batch
 * @return Sum of subsequent batches. A batch is sum of terms (1/k) where k = { n, ..., (n+N)-1) }
 * @throws None.
 *
 * Example:
 * @code
 * float sum = harmonic(N);
 * @endcode
 */
float harmonic_bunch(int N){

    float groupsum = 0;
    int Nmax = 100000000;
    int Cmax = Nmax / N;
    float sum;
    float previous_sum;

    for (int c=1; c<=Cmax; c++){
        sum = 0; 
        previous_sum = 0;

        for (int i=(c-1)*N+1; i<=c*N; i++) {
            previous_sum = sum;
            sum += 1.0/i;

            if (previous_sum == sum){
                cout << "float resolution limit at iteration " << i << endl;
                break;
            } 
        }
        groupsum += sum;
    }
    return groupsum;
}


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
