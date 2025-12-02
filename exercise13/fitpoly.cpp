#include <stdio.h>
#include <math.h>
#include <gsl/gsl_multifit.h>

/**
 * @brief General linear fitting for primitive polynomials of order p-1
 * @brief The function to be modelled is f(x) = sin(pi*x), x in [-2, 2]
 * @file fitpoly.cpp
 * @param p number of parameters (degree of polynomial + 1)
 * @param n number of data points
 * @return optimized parameters c
 */
double* fitpoly(int p, int n) {
    // Use GSL multifit linear least-squares (design matrix approach)

    double x_data[n], y_data[n];
    for (int i = 0; i < n; ++i) {
        x_data[i] = -2.0 + 4.0 * i / (n - 1);
        y_data[i] = sin(M_PI * x_data[i]);
    }

    // Build design matrix X (n x p) and vector y
    gsl_matrix* X = gsl_matrix_alloc(n, p);
    gsl_vector* y = gsl_vector_alloc(n);

    for (int i = 0; i < n; ++i) {
        gsl_vector_set(y, i, y_data[i]);
        for (int j = 0; j < p; ++j) {
            gsl_matrix_set(X, i, j, pow(x_data[i], j));
        }
    }

    // Output parameters and covariance
    gsl_vector* c = gsl_vector_alloc(p);
    gsl_matrix* cov = gsl_matrix_alloc(p, p);
    double chisq;

    // Allocate workspace required by gsl_multifit_linear
    gsl_multifit_linear_workspace* work = gsl_multifit_linear_alloc(n, p);
    int status = -1;
    if (work) {
        status = gsl_multifit_linear(X, y, c, cov, &chisq, work);
        gsl_multifit_linear_free(work);
    }

    gsl_matrix_free(X);
    gsl_vector_free(y);
    gsl_matrix_free(cov);
    return gsl_vector_ptr(c, 0);
}


/**
 * @brief Evaluate polynomial in a vector of x points, x in [-2, 2]
 * @file fitpoly.cpp
 * @param c pointer to polynomial coefficients
 * @param p number of parameters (degree of polynomial + 1)
 * @param m number of x points
 * @param x_data pointer to output x points
 * @param y_data pointer to output y points
 * @return void
 */
void evalpoly(double* c, int p, int m, double* x_data, double* y_data) {
    for (int i = 0; i < m; ++i) {
        double x = -2.0 + 4.0 * i / (m - 1);
        double y = 0.0;
        for (int j = 0; j < p; ++j) {
            y += c[j] * pow(x, j);
        }
        x_data[i] = x;
        y_data[i] = y;
    }
}