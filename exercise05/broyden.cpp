#include <iostream>
#include <string>
#include <cmath>
#include <numbers>
#include <Eigen/Core>
#include <Eigen/Dense>
 
using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;


// Hard-coded function f for broyden
VectorXd f(VectorXd x) {
    VectorXd out(2);
    out(0) = exp(-(pow(x(0),2)+pow(x(1),2)))-(1.0/8.0);
    out(1) = sin(x(0))-cos(x(1));
    return out;
}

// Hard-coded Jacobian inverse Jinv for broyden
MatrixXd Jinv(VectorXd x) {
    MatrixXd out(2,2);
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
    double tolerance = 1.0e-9;
    VectorXd x, xprev, y, s, stransB;

    MatrixXd B = Jinv(x_init);

    xprev = x_init;
    for (int i = 0; i < imax; ++i) {
        x = xprev - (B * f(xprev));
        s = x - xprev;
        // termination condition
        if (s.norm() < tolerance) break;
        y = f(x) - f(xprev);
        stransB = s.transpose() * B;
        B += (s-B*y)*stransB / stransB.dot(y);
    } 
    return x;  

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
