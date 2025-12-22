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
        os.path.join(current_dir, '..', 'build', 'runtime'),

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

add_solver_to_path('exercise10')

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