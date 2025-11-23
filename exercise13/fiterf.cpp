#include <stdio.h>
#include <math.h>
#include <gsl/gsl_multifit.h>

/**
 * @brief Three alternative linear fittings on the erf function
 * @brief The dataset is 11 x-points x_i = (i-1)/10 and y_i = erf(x_i) for i=1,...,11
 * @file fiterf.cpp
 * @param n number of parameters
 * @param model_type type of mode:
 * @param   'a' : polynomial of degree n-1
 * @param   'b' : polynomial with odd powers only: y = p_1*x + p_2*x^3 + ... + p_n*x^(2n-1)
 * @param   'c' : using z = 1/(1+x), y = p_1 + exp(-x^2)*(p_2 + p_3*z + p_4*z^2 + ... + p_n*z^(n-2))
 * @return optimized parameters p_i
 */
double* fiterf(int n, char model_type) {
    // Use GSL multifit linear least-squares (design matrix approach)

    const int N = 11;
    double x_data[N], y_data[N];
    for (int i = 0; i < N; ++i) {
        x_data[i] = i / 10.0;
        y_data[i] = erf(x_data[i]);
    }

    // Build design matrix X (N x n) and vector y
    gsl_matrix* X = gsl_matrix_alloc(N, n);
    gsl_vector* y = gsl_vector_alloc(N);

    for (int i = 0; i < N; ++i) {
        double x = x_data[i];
        double z = 1.0 / (1.0 + x);
        gsl_vector_set(y, i, y_data[i]);

        for (int j = 0; j < n; ++j) {
            double val = 0.0;
            if (model_type == 'a') {
                val = pow(x, j);                     // polynomial degree j
            } else if (model_type == 'b') {
                val = pow(x, 2 * j + 1);             // odd powers
            } else if (model_type == 'c') {
                if (j == 0) {
                    val = 1.0;
                } else {
                    val = exp(-x * x) * pow(z, j - 1);
                }
            }
            gsl_matrix_set(X, i, j, val);
        }
    }

    // Output parameters and covariance
    gsl_vector* c = gsl_vector_alloc(n);
    gsl_matrix* cov = gsl_matrix_alloc(n, n);
    double chisq;

    // Allocate workspace required by gsl_multifit_linear
    gsl_multifit_linear_workspace* work = gsl_multifit_linear_alloc(N, n);
    int status = -1;
    if (work) {
        status = gsl_multifit_linear(X, y, c, cov, &chisq, work);
        gsl_multifit_linear_free(work);
    }

    // If failure, still attempt to return zeros
    double* p_opt = new double[n];
    if (status == GSL_SUCCESS) {
        for (int i = 0; i < n; ++i) {
            p_opt[i] = gsl_vector_get(c, i);
        }
    } else {
        for (int i = 0; i < n; ++i) p_opt[i] = 0.0;
    }

    // Cleanup
    gsl_matrix_free(X);
    gsl_vector_free(y);
    gsl_vector_free(c);
    gsl_matrix_free(cov);

    return p_opt;
}



