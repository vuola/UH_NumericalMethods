#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;

void shootingSolver(double a, double b, int N, double y0, double y1, double* x, double* y); 

// Function to display help message
void displayHelp() {
    cout << endl;
    cout << "shootingSolver - solve ordinary differential equations using the shooting method" << endl << endl;
    cout << "Usage:" << endl;
    cout << "  shootingSolver a b N y0 y1" << endl;
    cout << "  shootingSolver --help" << endl << endl;
    cout << "Flags:" << endl;
    cout << "  --help        display help message" << endl;
    cout << "Arguments:" << endl;
    cout << "  a            left endpoint of the interval" << endl;
    cout << "  b            right endpoint of the interval" << endl;
    cout << "  N            number of steps" << endl;
    cout << "  y0           initial value of y" << endl;
    cout << "  y1           final value of y" << endl << endl;
}

// Helper function to generate an error message for incorrect argument count
string getArgumentCountErrorMessage(const string& functionName, int expectedCount, int actualCount) {
    return functionName + " requires " + to_string(expectedCount) +
           " arguments, but " + to_string(actualCount) + " were provided.";
}

// Main function implementing command line 
int main(int argc, char** argv){

    if (argc == 1) { // The first argument is the program name
        cerr << getArgumentCountErrorMessage(argv[0], 5, argc - 1) << endl;
        return 1;
    }

    string flag = argv[1];

    if (flag == "--help" || flag == "-h" || flag == "-H") {
        displayHelp();
        return 0;
    } 
        
    if (argc == 6) {
            double arg1 = stod(argv[1]);
            double arg2 = stod(argv[2]);
            int arg3 = stoi(argv[3]);
            double arg4 = stod(argv[4]);
            double arg5 = stod(argv[5]);
            double* x = new double[arg3 + 1];
            double* y = new double[arg3 + 1];
            shootingSolver(arg1, arg2, arg3, arg4, arg5, x, y);
            for (int i = 0; i <= arg3; i++) {
                cout.setf(ios::fixed);
                cout.precision(6);
                cout << x[i] << " " << y[i] << endl;
            }
            delete[] x;
            delete[] y;
            return 0;
    }

    cerr << getArgumentCountErrorMessage(argv[0], 6, argc - 1) << endl;
    return 1;

}