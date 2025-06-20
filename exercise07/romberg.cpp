
#include <iostream>
#include <string>
#include <cmath>
#include <numbers>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iomanip>
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;
const int MAXN = 20; // Maximum number of Romberg levels


double f1(double x)
{
    return sin(pow(x, 0.5));
}

double f2(double x)
{
    return sin(pow(x, 0.5)) - pow(x, 0.5);
}

void Romberg(double (*f)(double x), double a, double b, int n, double R[][MAXN])
{
    int i, j, k, kmax=1;
    double h, sum;
    h = b-a; R[0][0] = (h/2.0)*(f(a)+f(b));
    for (i=1; i<=n; i++) {
        h = h/2.0; sum = 0;
        kmax = kmax*2;
    /* Trapezoidal estimate R(i,0) */
    for (k=1; k<=kmax-1; k+=2)
        sum += f(a+k*h);
    R[i][0] = 0.5*R[i-1][0]+sum*h;
    /* Successive R(i,j) */
    for(j=1; j<=i; j++)
        R[i][j] = R[i][j-1] +(R[i][j-1]-R[i-1][j-1])/(pow(4.0,(double)j)-1.0);
    }
}

// Test the Romberg integration method
int main()
{
    double a = 0.0, b = 1.0;
    int n = 5; // Number of Romberg levels
    double R[MAXN][MAXN]; // Romberg table
    Romberg(f1, a, b, n, R);
    cout << "Romberg integration results for f1(x) = sin(sqrt(x)):" << endl;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            cout << setw(10) << setprecision(6) << R[i][j] << " ";
        }
        cout << endl;
    }
}