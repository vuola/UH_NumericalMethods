import numpy as np
import matplotlib.pyplot as plt
import os
import sys

# Get the absolute path to the build directory (relative to the script's location)
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, '..', 'build', 'exercise13')

# Append the build directory to sys.path
sys.path.append(build_dir)

# Import the self-made module from the build directory
import fitpoly as fitpoly

# @param degrees array of number of parameters
# @param n number of data points for fitting
# @param m number of evaluation points
# @param output_filename optional filename to save the plot
def plot_fitpoly_results(degrees, n, m, output_filename = None):
    
    # Plot the error function and the fitted polynomial.
    # Mark the fitting points with red circles.
    plt.figure(figsize=(8, 5))
    plt.title('Fitted sin(pi*x) function using fitpoly_primitive')
    plt.xlabel('x')
    plt.ylabel('Value')
    plt.grid()

    max_errors = []

    for deg in degrees:
        # Evaluate the fitted polynomial
        data = fitpoly.evaluateFitpoly(deg, n, m)

        # Extract x and fitted values
        x = data[:, 0]
        f_values = data[:, 1]
        fitted_values = data[:, 2]

        # Plot the fitted polynomial. Expect overrun and keep y between -5 and 5
        plt.plot(x, fitted_values, label=f'Degree {deg}')
        plt.ylim(-5, 5)

        # Return the L1 error between the fitted and actual error function
        l1_error = np.sum(np.abs(f_values - fitted_values))
        max_errors.append(l1_error)


    plt.plot(x, f_values, label='Function sin(pi*x)', color='black', linewidth=2)

    # Create an array of the fitting points x in [-2, 2] with n fitting points
    F = fitpoly.evaluateF(n)
    plt.scatter(F[:, 0], F[:, 1], color='red', label='Fitting Points')
    plt.legend()


    if output_filename:
        plt.savefig(output_filename)

    return max_errors


num_params_list_a = [5, 10, 15, 20, 25]
max_errors = plot_fitpoly_results(num_params_list_a, 25, 1000, 'fitpoly_results.png')

print("L1 errors for different polynomial degrees:")
for deg, err in zip(num_params_list_a, max_errors):
    print(f"Degree {deg}: L1 error = {err}")

# Plot the L1 error as function of polynomial degree
plt.figure(figsize=(8, 5))
plt.title('L1 Error vs Polynomial Degree')
plt.xlabel('Polynomial Degree')
plt.ylabel('L1 Error')
plt.semilogy(num_params_list_a, max_errors, marker='o', label='fitpoly')
plt.grid()
plt.legend()
plt.savefig('fitpoly_error_vs_degree.png')

