import numpy as np
import matplotlib.pyplot as plt
import os
import sys

# Get the absolute path to the build directory (relative to the script's location)
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, '..', 'build', 'exercise10')

# Append the build directory to sys.path
sys.path.append(build_dir)

# Load column data from text file
data = np.loadtxt('data.txt')

# Calculate the mean and variance
mean = np.mean(data)
variance = np.var(data)

# Print the original mean and variance
print("Mean:", mean)
print("Variance:", variance)

# Scale the data so that the mean is 3.7 and
# variance is 76.6

data = (data - mean) / np.sqrt(variance) * np.sqrt(76.6) + 3.7

# Print the scaled data in a column with 4 decimal places
print("Scaled Data:")
for value in data:
    print(f"{value:.4f}")

# Calculate the mean and variance of the scaled data
sc_mean = np.mean(data)
sc_variance = np.var(data)

# Print the scaled mean and variance
print("Scaled mean:", sc_mean)
print("Scaled variance:", sc_variance)

# Perform Chi2 test to see if the distribution is Gaussian
Chi2 = np.sum(((data - sc_mean) ** 2) / sc_variance)

# Print the result
print("Chi2:", Chi2)