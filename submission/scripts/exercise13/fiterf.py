import numpy as np
import matplotlib.pyplot as plt
import os
import sys

def add_solver_to_path(exercise_name):
    """
    Makes eigenpy modules importable in both:
    - development repository
    - submission folder layout
    """
    current_dir = os.path.dirname(os.path.abspath(__file__))

    candidate_paths = [
        # Development layout:
        os.path.join(current_dir, '..', 'build', exercise_name),

        # Submission layout:
        os.path.join(current_dir, '..', '..', 'python'),
    ]

    for path in candidate_paths:
        if os.path.isdir(path):
            sys.path.insert(0, path)
            return

    raise RuntimeError(
        f"Could not locate Python modules for {exercise_name}. "
        f"Tried: {candidate_paths}"
    )

add_solver_to_path('exercise13')

# Import the self-made module from the build directory
import fiterf as fiterf

def plot_fiterf_results(num_param, model_type, num_points, output_filename = None):

    # Plot the error function and the fitted error function.
    # Mark the fitting points with red circles.
    plt.figure(figsize=(8, 5))
    plt.title('Fitted Error Function using fiterf')
    plt.xlabel('x')
    plt.ylabel('Value')
    plt.grid()

    max_errors = []

    for npar in num_param:
        # Evaluate the fitted error function
        data = fiterf.evaluateFiterf(npar, model_type, num_points)

        # Extract x and fitted values
        x = data[:, 0]
        erf_values = data[:, 1]
        fitted_values = data[:, 2]

        plt.plot(x, fitted_values, label=f'{npar} params')

        # Return the maximum absolute error between the fitted and actual error function
        max_abs_error = np.max(np.abs(erf_values - fitted_values))
        max_errors.append(max_abs_error)


    plt.plot(x, erf_values, label='Error Function (erf)', color='black', linewidth=2)

    # Create an array of the fitting points x_i = (i-1)/10 and for i=1,...,11
    fitting_x = np.array([(i-1)/10 for i in range(1, 12)])
    fitting_y = np.array([np.math.erf(xi) for xi in fitting_x])
    plt.scatter(fitting_x, fitting_y, color='red', label='Fitting Points')
    plt.legend()


    if output_filename:
        plt.savefig(output_filename)

    return max_errors


# 
num_params_list_a = list(range(1, 12))
max_errors_A = plot_fiterf_results(num_params_list_a, 'a', 1000, 'fit_erf_results_a.png')

num_params_list_b = list(range(1, 6))
max_errors_B = plot_fiterf_results(num_params_list_b, 'b', 1000, 'fit_erf_results_b.png')

num_params_list_c = list(range(1, 6))
max_errors_C = plot_fiterf_results(num_params_list_c, 'c', 1000, 'fit_erf_results_c.png')
# Plot the maximum absolute error as function of number of parameters
plt.figure(figsize=(8, 5))
plt.semilogy(num_params_list_a, max_errors_A, marker='o', label='Model (a)')
plt.semilogy(num_params_list_b, max_errors_B, marker='s', label='Model (b)')
plt.semilogy(num_params_list_c, max_errors_C, marker='^', label='Model (c)')
plt.title('Maximum Absolute Error of Fitted Error Function vs Number of Parameters')
plt.xlabel('Number of Parameters')
plt.ylabel('Maximum Absolute Error')
plt.xticks(num_params_list_a)
plt.legend()
plt.grid()
plt.savefig('max_absolute_error_fit_erf.png')