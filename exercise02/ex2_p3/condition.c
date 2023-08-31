#include <stdio.h>
#include <lapacke.h>

extern void dgecon_(const char *norm, const int *n, double *A, const int *lda, const double *anorm, double *rcond, double *work, int *iwork, int *info);

int main() {
    int n = 3; // Order of the matrix
    double A[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 10.0}; // Matrix A in row-major order
    int lda = n;
    double anorm = LAPACKE_dlange(LAPACK_COL_MAJOR, '1', n, n, A, lda);

    double rcond;
    double work[4*n];
    int iwork[n];
    int info;

    dgecon_("1", &n, A, &lda, &anorm, &rcond, work, iwork, &info);

    if (info == 0) {
        printf("Reciprocal condition number: %lf\n", rcond);
    } else {
        printf("Error occurred: info = %d\n", info);
    }

    return 0;
}
