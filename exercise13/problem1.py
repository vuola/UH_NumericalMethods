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
import fiterf as fiterf

def plot_fiterf_results(num_param, model_type, num_points, output_filename = None):
    # Evaluate the fitted error function
    data = fiterf.evaluateFiterf(num_param, model_type, num_points)

    # Extract x and fitted values
    x = data[:, 0]
    erf_values = data[:, 1]
    fitted_values = data[:, 2]

    # Create an array of the fitting points x_i = (i-1)/10 and for i=1,...,11
    fitting_x = np.array([(i-1)/10 for i in range(1, 12)])
    fitting_y = np.array([np.math.erf(xi) for xi in fitting_x])


    # Plot the error function and the fitted error function.
    # Mar k the fitting points with red circles.
    plt.figure(figsize=(8, 5))
    plt.plot(x, erf_values, label='Error Function (erf)')
    plt.plot(x, fitted_values, label=f'Fitted Error Function ({model_type})')
    plt.scatter(fitting_x, fitting_y, color='red', label='Fitting Points')
    plt.title('Fitted Error Function using fiterf')
    plt.xlabel('x')
    plt.ylabel('Value')
    plt.legend()
    plt.grid()
    if output_filename:
        plt.savefig(output_filename)

    # Return the maximum absolute error between the fitted and actual error function
    max_abs_error = np.max(np.abs(erf_values - fitted_values))
    return max_abs_error


# Run number of parameters from 1 to 11 and plot the maximum absolute error as function of number of parameters
num_params_list = list(range(1, 12))
max_errors_model_A = []
max_errors_model_B = []
max_errors_model_C = []
for n in num_params_list:
    max_error_A = plot_fiterf_results(n, 'a', 1000)
    max_errors_model_A.append(max_error_A)

    max_error_B = plot_fiterf_results(n, 'b', 1000)
    max_errors_model_B.append(max_error_B)

    max_error_C = plot_fiterf_results(n, 'c', 1000)
    max_errors_model_C.append(max_error_C)


# Plot the maximum absolute error as function of number of parameters
plt.figure(figsize=(8, 5))
plt.semilogy(num_params_list, max_errors_model_A, marker='o', label='Model (a)')
plt.semilogy(num_params_list, max_errors_model_B, marker='s', label='Model (b)')
plt.semilogy(num_params_list, max_errors_model_C, marker='^', label='Model (c)')
plt.title('Maximum Absolute Error of Fitted Error Function vs Number of Parameters')
plt.xlabel('Number of Parameters')
plt.ylabel('Maximum Absolute Error')
plt.xticks(num_params_list)
plt.legend()
plt.grid()
plt.savefig('max_absolute_error_fiterf.png')