/**
 * @brief Solve the equation y''(x)+y(x)=0 with initial conditions.
 * @file rungeKuttaSolver.cpp
 * @param a Initial value of x
 * @param b Final value of x
 * @param N Number of steps
 * @param y0 Initial value of y at x=a
 * @param yp0 Initial value of y' at x=a
 * @param x Array to store x values (size N+1)
 * @param y Array to store y values (size N+1)
 */
void rungeKuttaSolver(double a, double b, int N, double y0, double yp0, double* x, double* y)
{
    // A conversion to a system of first-order equations
    // y1 = y
    // y2 = y'
    // y1' = y2
    // y2' = -y1

    // Step size
    double h = (b - a) / N;

    // Initial conditions
    x[0] = a;
    y[0] = y0;
    double y1 = y0;   // y
    double y2 = yp0;  // y'

    // Runge-Kutta iteration
    for (int i = 0; i < N; i++) {
        // Current x value
        x[i + 1] = a + (i + 1) * h;

        // Runge-Kutta coefficients
        double k1y1 = h * y2;
        double k1y2 = -h * y1;

        double k2y1 = h * (y2 + 0.5 * k1y2);
        double k2y2 = -h * (y1 + 0.5 * k1y1);

        double k3y1 = h * (y2 + 0.5 * k2y2);
        double k3y2 = -h * (y1 + 0.5 * k2y1);

        double k4y1 = h * (y2 + k3y2);
        double k4y2 = -h * (y1 + k3y1);

        // Update y values
        y1 += (k1y1 + 2 * k2y1 + 2 * k3y1 + k4y1) / 6;
        y2 += (k1y2 + 2 * k2y2 + 2 * k3y2 + k4y2) / 6;

        // Store results
        y[i + 1] = y1;
        x[i + 1] = x[i] + h;
    }
}
