import numpy as np
import matplotlib.pyplot as plt
import os
import sys

# Get the absolute path to the build directory (relative to the script's location)
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, '..', 'build', 'exercise10')

# Append the build directory to sys.path
sys.path.append(build_dir)

# Import the self-made module from the build directory
import verifyclt as vclt

def plot_clt_distributions(num_samples, output_filename):
    # Create test distributions
    data10 = vclt.verifyclt(num_samples)

    # For reference normal distributions, check mean and stddev. Weight x points with p values.
    mean_normal = []
    std_normal = []
    for i in range(3):
        x = data10[:, 2*i]
        p = data10[:, 2*i + 1]
        mean = np.sum(x * p) / np.sum(p)
        variance = np.sum((x - mean)**2 * p) / np.sum(p)
        stddev = np.sqrt(variance)
        mean_normal.append(mean)
        std_normal.append(stddev)

    # Create reference normal distributions
    x_ref = [data10[:, 0], data10[:, 2], data10[:, 4]]
    pref_normal = []

    for i in range(3):
        mean = mean_normal[i]
        stddev = std_normal[i]
        pref = (1 / (stddev * np.sqrt(2 * np.pi))) * np.exp(-0.5 * ((x_ref[i] - mean) / stddev) ** 2)
        pref_normal.append(pref)
        # Scale pref_normal to match the test distributions
        scale_factor = np.max(data10[:, 2*i + 1]) / np.max(pref)
        pref_normal[i] *= scale_factor

    # Plot distributions with reference normals
    plt.figure(figsize=(10, 6))
    labels = ['Uniform', 'Exponential', 'Lorentz']
    for i in range(3):
        x = data10[:, 2*i]
        p = data10[:, 2*i + 1]
        plt.subplot(3, 1, i + 1)
        plt.plot(x, p, label=labels[i])
        plt.plot(x_ref[i], pref_normal[i], linestyle='--', label='Reference Normal')
        plt.legend()
        plt.grid()
        plt.xlabel('x')
        plt.ylabel('Probability Density')
    plt.tight_layout()
    plt.savefig(output_filename)


# Call the function to plot and save the distributions

plot_clt_distributions(3, 'problem2_K3.png')
plot_clt_distributions(10, 'problem2_K10.png')
plot_clt_distributions(30, 'problem2_K30.png')
plot_clt_distributions(100, 'problem2_K100.png')