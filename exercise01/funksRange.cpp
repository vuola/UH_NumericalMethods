#include <iostream>
#include <utility>
#include <Eigen/Core>
 
using Eigen::MatrixXd;
using Eigen::ArrayXd;
using Eigen::VectorXd;

std::pair<double, double> funks(double x);

MatrixXd funksRange(double first, double last, int N)
{
    MatrixXd m(3, N);
    VectorXd Xpoints = VectorXd::LinSpaced(N, first, last);
    std::pair<double,double> p;

    for (int i=0; i<N; ++i) {
        m(0,i) = Xpoints(i);
        p = funks(m(0,i));
        m(1,i) = p.first;
        m(2,i) = p.second;
    }
    return m;
}