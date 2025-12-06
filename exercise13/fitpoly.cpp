#include <stdio.h>
#include <math.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>
#define BASIS_PRIMITIVE 0
#define BASIS_REGULATED 0
#define BASIS_LEGENDRE 1

/**
 * @brief Define a generic basis function X_j(x) to be used in polynomial 
 * fitting as an interchangeable component. First define a primitive polynomial.
 * @param j index of the basis function
 * @param x input variable
 * @return value of the basis function at x
 */
double X_primitive(int j, double x) {
    return pow(x, j);
}

/**
 * @brief Define a regulated basis function X_j(x) to be used in polynomial 
 * fitting as an interchangeable component. This basis is intended to improve
 * numerical stability.
 * @param j index of the basis function
 * @param x input variable
 * @return value of the basis function at x
 */
double X_regulated(int j, double x) {
    return pow(x / 2.0, j);
}

/**
 * @brief Define a Legendre polynomial basis function X_j(x) to be used in polynomial 
 * fitting as an interchangeable component. This basis is intended to improve
 * numerical stability.
 * @param j index of the basis function
 * @param x input variable
 * @param scale scaling factor for x
 * @return value of the basis function at x
 */
double X_legendre(int j, double x, double scale) {
    double x_scaled = x / scale;
    if (j == 0) {
        return 1.0;
    } else if (j == 1) {
        return x_scaled;
    } else {
        return ((2 * j - 1) * x_scaled * X_legendre(j - 1, x, scale) - (j - 1) * X_legendre(j - 2, x, scale)) / j;
    }
}


/**
 * @brief Simplified fitting using normal equations with eigen decomposition of alpha.
 * @brief The purpose is to investigate numerical stability. Eigenvalues are plotted.
 * @brief The function to be modelled is f(x) = sin(pi*x), x in [-2, 2]
 * @file fitpoly.cpp
 * @param p number of parameters (degree of polynomial + 1)
 * @param n number of data points
 * @return optimized parameters c
 */
double* fitpoly_primitive(int p, int n) {

    // screen out very small eigenvalues
    #define MINIMUM_EIGENVALUE 1e-3

    double x_data[n], y_data[n];
    for (int i = 0; i < n; ++i) {
        x_data[i] = -2.0 + 4.0 * i / (n - 1);
        y_data[i] = sin(M_PI * x_data[i]);
    }

    // Build alpha matrix A and beta vector b using GSL data structures
    // Use generic polynomial basis X_j(x) = x^j

    gsl_matrix* A = gsl_matrix_alloc(p, p);
    gsl_vector* b = gsl_vector_alloc(p);
    gsl_vector* c = gsl_vector_alloc(p);


    if (BASIS_PRIMITIVE) {
        for (int i = 0; i < p; ++i) {
            double bi = 0.0;

            for (int k = 0; k < n; ++k) {
                bi += y_data[k] * X_primitive(i, x_data[k]);
            }
            gsl_vector_set(b, i, bi);

            for (int j = 0; j < p; ++j) {
                double aij = 0.0;
                for (int k = 0; k < n; ++k) {
                    aij += X_primitive(i, x_data[k]) * X_primitive(j, x_data[k]);
                }
                gsl_matrix_set(A, i, j, aij);
            }
        }

    } else if (BASIS_REGULATED) {
        for (int i = 0; i < p; ++i) {
            double bi = 0.0;

            for (int k = 0; k < n; ++k) {
                bi += y_data[k] * X_regulated(i, x_data[k]);
            }
            gsl_vector_set(b, i, bi);

            for (int j = 0; j < p; ++j) {
                double aij = 0.0;
                for (int k = 0; k < n; ++k) {
                    aij += X_regulated(i, x_data[k]) * X_regulated(j, x_data[k]);
                }
                gsl_matrix_set(A, i, j, aij);
            }
        }

    } else if (BASIS_LEGENDRE) {
        for (int i = 0; i < p; ++i) {
            double bi = 0.0;

            for (int k = 0; k < n; ++k) {
                bi += y_data[k] * X_legendre(i, x_data[k], 2.0);
            }
            gsl_vector_set(b, i, bi);

            for (int j = 0; j < p; ++j) {
                double aij = 0.0;
                for (int k = 0; k < n; ++k) {
                    aij += X_legendre(i, x_data[k], 2.0) * X_legendre(j, x_data[k], 2.0);
                }
                gsl_matrix_set(A, i, j, aij);
            }
        }
    }

    // Run eigendecomposition to investigate numerical stability
    gsl_vector* eval = gsl_vector_alloc(p);
    gsl_matrix* evec = gsl_matrix_alloc(p, p);
    gsl_eigen_symmv_workspace* w = gsl_eigen_symmv_alloc(p);
    gsl_eigen_symmv(A, eval, evec, w);
    gsl_eigen_symmv_free(w);

    printf("Eigenvalues of alpha matrix, p=%d:\n", p);
    float eigval;
    for (int i = 0; i < p; ++i) {
        eigval = gsl_vector_get(eval, i);
        printf("%g", eigval);
        if (eigval < MINIMUM_EIGENVALUE) {
            printf("  <-- screened\n");
        } else {
            printf("\n");
        }
    }

    // Screen out very small eigenvalues
    for (int i = 0; i < p; ++i) {
        if (gsl_vector_get(eval, i) < MINIMUM_EIGENVALUE) {
            gsl_vector_set(eval, i, MINIMUM_EIGENVALUE);
        }
    }

    // Reconstruct alpha matrix with screened eigenvalues
    gsl_matrix_set_zero(A);
    for (int i = 0; i < p; ++i) {
        double lambda = gsl_vector_get(eval, i);
        gsl_vector_view ei = gsl_matrix_column(evec, i);
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < p; ++k) {
                double val = gsl_matrix_get(A, j, k) + lambda * gsl_vector_get(&ei.vector, j) * gsl_vector_get(&ei.vector, k);
                gsl_matrix_set(A, j, k, val);
            }
        }
    }

    // Solve for c in Ac = b using GSL linear solver
    gsl_permutation* perm = gsl_permutation_alloc(p);
    int signum;
    gsl_linalg_LU_decomp(A, perm, &signum);
    gsl_linalg_LU_solve(A, perm, b, c);

    gsl_matrix_free(A);
    gsl_vector_free(b);
    gsl_permutation_free(perm);

    gsl_vector_free(eval);
    gsl_matrix_free(evec);
    return gsl_vector_ptr(c, 0);

}


/**
 * @brief General linear fitting for selected polynomial basis.
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
            if (BASIS_PRIMITIVE) {
                double x_ij = X_primitive(j, x_data[i]);
                gsl_matrix_set(X, i, j, x_ij);
            } else if (BASIS_REGULATED) {
                double x_ij = X_regulated(j, x_data[i]);
                gsl_matrix_set(X, i, j, x_ij);
            } else if (BASIS_LEGENDRE) {
                double x_ij = X_legendre(j, x_data[i], 2.0);
                gsl_matrix_set(X, i, j, x_ij);
            }
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
        if (BASIS_PRIMITIVE) {
            for (int j = 0; j < p; ++j) {
                y += c[j] * pow(x, j);
            }
        } else if (BASIS_REGULATED) {
            for (int j = 0; j < p; ++j) {
                y += c[j] * pow(x / 2.0, j);
            }
        } else if (BASIS_LEGENDRE) {
            for (int j = 0; j < p; ++j) {
                y += c[j] * X_legendre(j, x, 2.0);
            }
        }
        x_data[i] = x;
        y_data[i] = y;
    }
}


