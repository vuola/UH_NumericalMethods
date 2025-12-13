#include <iostream>
#include <utility>
#include <Eigen/Core>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <cmath>
using namespace boost::accumulators;
 
using Eigen::MatrixXd;
using Eigen::VectorXi;
using Eigen::VectorXd;

double err_propag(int N, double dq);

MatrixXd jacobiRange(VectorXi xN, VectorXd xdq, int k)
{
    int kN = xN.size();
    int kdq = xdq.size();
    int sets = kN*kdq;
    MatrixXd D(4, sets);

    // Define an accumulator set for calculating the mean and the variance
    accumulator_set<double, stats<tag::mean, tag::variance> > acc;

    for (int n=0; n<kN; ++n) {
        for (int q=0; q<kdq; ++q) {
            int id = n*kN+q;
            for (int i=0; i<k; ++i) {
                acc(err_propag(xN(n), xdq(q)));
            }
            D(0,id) = xN(n);
            D(1,id) = xdq(q);
            D(2,id) = mean(acc);
            D(3,id) = sqrt(variance(acc));
        }
    }
    return D;
}