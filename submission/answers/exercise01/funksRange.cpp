#include <iostream>
#include <utility>
#include <Eigen/Core>
 
using Eigen::MatrixXd;
using Eigen::ArrayXd;
using Eigen::VectorXd;

std::pair<double, double> funks(double x);
std::pair<double, double> funks_Taylor(double x);
std::pair<double, double> funksError(double z, int n);

MatrixXd funksRange(double first, double last, int N)
{
    MatrixXd m(11, N);
    VectorXd Xpoints = VectorXd::LinSpaced(N, first, last);
    std::pair<double,double> f;
    std::pair<double,double> T;
    std::pair<double,double> e1;
    std::pair<double,double> e2;
    std::pair<double,double> e3;

    for (int i=0; i<N; ++i) {
        m(0,i) = Xpoints(i);
        f = funks(m(0,i));
        T = funks_Taylor(m(0,i));

        e1 = funksError(m(0,i),1);
        e2 = funksError(m(0,i),2);
        e1 = funksError(m(0,i),3);

        m(1,i) = f.first;
        m(2,i) = T.first;
        m(3,i) = f.second;
        m(4,i) = T.second;

        m(5,i) = e1.first;
        m(6,i) = e2.first;
        m(7,i) = e3.first;

        m(8,i) = e1.second;
        m(9,i) = e2.second;
        m(10,i) = e3.second;

    }
    return m;
}