#include <iostream>
#include <stdlib.h>
#include <Eigen/Dense>

using namespace std;
using Eigen::VectorXd;


int main(int argc, char** argv){

    if (argc!=2) {
        fprintf(stderr,"Usage: %s k\n",argv[0]);
        return (1);
    }

    cout << harmonic(argv[1]) << endl;
}
