import numpy as np
import matplotlib.pyplot as plt
import scipy.special as sp
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

# Function for reading two-column data {v, f(v)} from a file into a N by 2 numpy array.
# Remove rows where either v or f(v) is zero.
def read_data_from_file(filename):
    data = np.loadtxt(filename)
    data = data[(data[:, 0] != 0) & (data[:, 1] != 0)]  # Remove rows where v or f(v) is zero
    return data

# Function for mapping the data {v, f(v)} to {x, g(x)}. The transformations are:
# x = v²
# g(x) = ln(f(v)/x)
# This transformation linearizes the Maxwell-Boltzmann distribution model
# f(v) = a * v^2 * exp(-v² / 2*b)
# into a linear form g(x) = ln(a) - x/(2*b) = c + m*x
# @param data N by 2 numpy array containing {v, f(v)}
# @return N by 2 numpy array containing {x, g(x)}
def transform_data(data):
    v = data[:, 0]
    f_v = data[:, 1]
    
    x = v**2
    g_x = np.log(f_v / x)
    
    transformed_data = np.column_stack((x, g_x))
    return transformed_data

# Function for mapping back the fitted parameters {c, m} to {a, b}
# g(x) = c + m*x is the linear form # where c = ln(a) and m = -1/(2*b)
# @param c intercept from the linear fit
# @param m slope from the linear fit
# @return a, b parameters of the Maxwell-Boltzmann distribution
def map_parameters(c, m):
    a = np.exp(c)
    b = -1 / (2 * m)
    return a, b


# Function to run the process of reading, transforming, fitting, and mapping back.
# @param filename input data file containing {v, f(v)}
# @param output_filename optional filename to save the plot
def process_maxwell_boltzmann_fit(filename, output_filename=None):

    # Read data from file
    data = read_data_from_file(filename)
    
    # Transform the data
    transformed_data = transform_data(data)
    x = transformed_data[:, 0]
    g_x = transformed_data[:, 1]
    
    # Fit a linear model to the transformed data
    coeffs = np.polyfit(x, g_x, 1)  # coeffs[0] = m, coeffs[1] = c
    m = coeffs[0]
    c = coeffs[1]

    # print(f"Fitted parameters from {filename}: c = {c}, m = {m}")
    
    # Map back to original parameters a and b
    a, b = map_parameters(c, m)
    
    print(f"Linear fit parameters from {filename}: a = {a}, b = {b}")
    
    # Plot the original data and the fitted Maxwell-Boltzmann distribution
    v_fit = np.linspace(0, np.max(data[:, 0]), 200)
    f_fit = a * v_fit**2 * np.exp(-v_fit**2 / (2 * b))
    
    plt.figure(figsize=(8, 5))
    plt.scatter(data[:, 0], data[:, 1], color='red', label='Data Points')
    plt.plot(v_fit, f_fit, label='Fitted Maxwell-Boltzmann Distribution')
    plt.title('Maxwell-Boltzmann Distribution, linear fit')
    plt.xlabel('Velocity v')
    plt.ylabel('f(v)')
    plt.legend()
    plt.grid()
    
    if output_filename:
        plt.savefig(output_filename)
    else:
        plt.show()


# Run the fitting process for the provided data files
process_maxwell_boltzmann_fit('ex13p4_d1.dat', 'maxwell_boltzmann_linear_d1.png')
process_maxwell_boltzmann_fit('ex13p4_d2.dat', 'maxwell_boltzmann_linear_d2.png')
process_maxwell_boltzmann_fit('ex13p4_d3.dat', 'maxwell_boltzmann_linear_d3.png')


# Nonlinear least squares fitting using scipy's Levenberg-Marquardt algorithm
# This function fits the Maxwell-Boltzmann distribution directly to the data
def nonlinear_fit_maxwell_boltzmann(filename, output_filename=None):
    from scipy.optimize import curve_fit

    # Define the Maxwell-Boltzmann distribution function
    def maxwell_boltzmann(v, a, b):
        return a * v**2 * np.exp(-v**2 / (2 * b))

    # Read data from file
    data = read_data_from_file(filename)
    v = data[:, 0]
    f_v = data[:, 1]

    # Initial guess for parameters a and b
    initial_guess = [0.013349452851293417, 349843.8289248972]

    # Perform the curve fitting
    params, covariance = curve_fit(maxwell_boltzmann, v, f_v, p0=initial_guess, method='lm')

    a_fit, b_fit = params
    print(f"Nonlinear fit parameters from {filename}: a = {a_fit}, b = {b_fit}")

    # Plot the original data and the fitted Maxwell-Boltzmann distribution
    v_fit = np.linspace(0, np.max(v), 200)
    f_fit = maxwell_boltzmann(v_fit, a_fit, b_fit)

    plt.figure(figsize=(8, 5))
    plt.scatter(v, f_v, color='red', label='Data Points')
    plt.plot(v_fit, f_fit, label='Fitted Maxwell-Boltzmann Distribution')
    plt.title('Maxwell-Boltzmann Distribution, nonlinear fit')
    plt.xlabel('Velocity v')
    plt.ylabel('f(v)')
    plt.legend()
    plt.grid()

    if output_filename:
        plt.savefig(output_filename)
    else:
        plt.show()


# Run the nonlinear fitting process for the provided data files
nonlinear_fit_maxwell_boltzmann('ex13p4_d1.dat', 'maxwell_boltzmann_nonlinear_d1.png')
nonlinear_fit_maxwell_boltzmann('ex13p4_d2.dat', 'maxwell_boltzmann_nonlinear_d2.png')
nonlinear_fit_maxwell_boltzmann('ex13p4_d3.dat', 'maxwell_boltzmann_nonlinear_d3.png')