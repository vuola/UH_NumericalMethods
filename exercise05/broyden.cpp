#include <iostream>
#include <string>
#include <cmath>
#include <numbers>
#include <Eigen/Core>
 
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;


// Hard-coded function f for broyden
VectorXd f(VectorXd x) {
    VectorXd out(2);
    out(0) = exp(-(pow(x(0),2)+pow(x(0),2)))-(1/8);
    out(1) = sin(x(0))-cos(x(1));
    return out;
}

// Hard-coded Jacobian inverse Jinv for broyden
MatrixXd Jinv(VectorXd x) {
    MarixXd out(2,2);
    out(0,0) = -2.0 * x(0) * exp(-(pow(x(0),2)+pow(x(0),2)));
    out(1,0) = cos(x(0));
    out(0,1) = -2.0 * x(1) * exp(-(pow(x(0),2)+pow(x(0),2)));
    out(1,1) = sin(x(1));
    return out.inverse();
}

/**
 * @brief broyden - solve roots of a 2-dimensional nonlinear function f using Broyden method
 * @return Returns a 2-vector r, vector elements are roots of f(x).
 *  
 * @throws None.
 *
 * @param x_init Initial x values for root search
 */
VectorXd broyden(VectorXd x_init) {

    int imax = 50;
    VectorXd x, xprev, y, s, strans;
    MatrixXd B = Jinv(x_init);

    xprev = x_init;
    for (int i = 0; i < imax; ++i) {
        x = xprev - B * f(x);
        s = x - xprev;
        // tähän lopetusehto
        y = f(x) - f(xprev);
        strans = s.transpose();
        B += (s-B*y)*strans*B / (s.trans*B*y);
    }   

}

int main() {
    VectorXd x_init(2);
    x_init(0) = 1;
    x_init(1) = 1;
    VectorXd r = broyden(x_init);
    cout << "Roots: " << r << endl;
    cout << "Error: " << f(r) << endl;
    return 0;
}
