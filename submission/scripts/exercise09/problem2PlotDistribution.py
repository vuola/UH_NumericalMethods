import numpy as np
import matplotlib.pyplot as plt
import os
import sys

# Get the absolute path to the build directory (relative to the script's location)
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, '..', 'build', 'exercise09')

# Append the build directory to sys.path
sys.path.append(build_dir)

# Import the self-made module from the build directory
import problem2 as p2
def plot_distribution(func_name, M=20):
    """
    Plot the distribution of a given function using the verifyDistribution function.
    
    Parameters:
    - func_name: Name of the function to plot ('exp' or 'lorentz').
    - M: Number of bins for the histogram.
    """
    # Call the verifyDistribution function
    result = p2.verifyDistribution(func_name, M)
    
    # Extract x and p values (numerical distribution) from the result
    x_values = result[0, :]
    p_values = result[1, :]
    # Extract pref (theoretical distribution) from the result
    pref = result[2, :]
    
    # Plotting
    plt.figure(figsize=(10, 6))
    plt.bar(x_values, p_values, width=(x_values[1] - x_values[0]), alpha=0.7, label='Numerical')
    plt.plot(x_values, pref, color='red', linewidth=2, label='Theoretical')
    plt.title(f'Distribution of {func_name} Function')
    plt.xlabel('x')
    plt.ylabel('Probability Density')
    plt.grid()
    plt.legend()
    plt.savefig(f'{func_name}_distribution.png')


if __name__ == "__main__":
# Plot distributions for both functions and store into files
    plot_distribution('exp', M=100)
 
    plot_distribution('lorentz', M=100)
    
