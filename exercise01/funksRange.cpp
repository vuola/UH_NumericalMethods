#include <iostream>
#include <utility>
#include <Eigen/Core>
 
using Eigen::MatrixXd;
using Eigen::ArrayXd;
using Eigen::VectorXd;

std::pair<double, double> funks(double x);
std::pair<double, double> funks_Taylor(double x);

MatrixXd funksRange(double first, double last, int N)
{
    MatrixXd m(5, N);
    VectorXd Xpoints = VectorXd::LinSpaced(N, first, last);
    std::pair<double,double> f;
    std::pair<double,double> T;

    for (int i=0; i<N; ++i) {
        m(0,i) = Xpoints(i);
        f = funks(m(0,i));
        T = funks_Taylor(m(0,i));
        m(1,i) = f.first;
        m(2,i) = T.first;
        m(3,i) = f.second;
        m(4,i) = T.second;
    }
    return m;
}