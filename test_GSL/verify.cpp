#include <stdio.h>
#include <math.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_errno.h>

// Example function: f(x) = (x - 2)^2 + 1
double my_f(double x, void *params) {
    return (x - 2.0) * (x - 2.0) + 1.0;
}

int main(void) {
    const gsl_min_fminimizer_type *T;
    gsl_min_fminimizer *s;
    gsl_function F;

    F.function = &my_f;
    F.params = NULL;

    double x_lower = 0.0;
    double x_upper = 5.0;
    double x_guess = 2.0;

    // Use Brent's method for minimization

    T = gsl_min_fminimizer_brent;
    s = gsl_min_fminimizer_alloc(T);
    gsl_min_fminimizer_set(s, &F, x_guess, x_lower, x_upper);

    int status, iter = 0;
    do {
        iter++;
        status = gsl_min_fminimizer_iterate(s);
        double m = gsl_min_fminimizer_x_minimum(s);
        x_lower = gsl_min_fminimizer_x_lower(s);
        x_upper = gsl_min_fminimizer_x_upper(s);
        status = gsl_min_test_interval(x_lower, x_upper, 1e-6, 0.0);

        printf("iter %d: x = %.7f\n", iter, m);
    } while (status == GSL_CONTINUE && iter < 100);

    gsl_min_fminimizer_free(s);
    return 0;
}
