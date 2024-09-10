#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include "bernstein_polynomial.hpp"

int main(int argc, char* argv[]) {
    int n, mt;
    double dt, x, y, t;
    double *b, *xa, *ya;
    char *argu;

    if (argc != 3) {
        std::cout << "usage: bezier n dt" << std::endl;
        return 0;
    }

    argu = argv[1];
    n = std::stoi(argu);
    argu = argv[2];
    dt = std::stod(argu);

    n = n - 1;
    b = new double[n + 1];
    xa = new double[n + 1];
    ya = new double[n + 1];

    for (int i = 0; i <= n; i++) {
        std::cin >> xa[i] >> ya[i];
    }

    mt = 1.0 / dt;
    for (int m = 0; m <= mt; m++) {
        t = dt * m;
        x = 0.0;
        y = 0.0;

        bernstein_poly(n, t, b);

        for (int i = 0; i <= n; i++) {
            y = y + ya[i] * b[i];
        }

        bernstein_poly(n, t, b);

        for (int i = 0; i <= n; i++) {
            x = x + xa[i] * b[i];
        }

        std::cout << x << " " << y << std::endl;
    }

    delete [] b;
    delete [] xa;
    delete [] ya;

    return 0;
}