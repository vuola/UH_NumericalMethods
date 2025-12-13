import numpy as np
import matplotlib.pyplot as plt
import os
import sys

# Get the absolute path to the build directory (relative to the script's location)
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, '..', 'build', 'exercise09')

# Append the build directory to sys.path
sys.path.append(build_dir)

# Use the self-created library
import mypi as mypi

# Call the verifyPi function and get the results
results = mypi.verifyPi()

# Plot the histograms for each value of n on the same graph
for i in range(3):
    plt.bar(results[:, i * 2], results[:, i * 2 + 1], width=0.01, label=f"n = {i + 2}")

# Add a vertical line indicating the accurate value of pi
plt.axvline(x=np.pi, color='r', linestyle='--', label='Actual π')

plt.title("Histograms for Different n Values")
plt.xlabel("Value")
plt.ylabel("Probability")

plt.tight_layout()
plt.savefig('pi_histograms.png')
plt.clf()

# Report distribution average by weighting x values with p values
print("Results for 2D case")

average = np.sum(results[:, 0] * results[:, 1]) / np.sum(results[:, 1])
print(f"Average value of π from the distribution n=2: {average}")

average = np.sum(results[:, 2] * results[:, 3]) / np.sum(results[:, 3])
print(f"Average value of π from the distribution n=3: {average}")

average = np.sum(results[:, 4] * results[:, 5]) / np.sum(results[:, 5])
print(f"Average value of π from the distribution n=4: {average}")

# Call the verifyPi3D function and get the results
results = mypi.verifyPi3D()

# Plot the histograms for 3D case
for i in range(3):
    plt.bar(results[:, i * 2], results[:, i * 2 + 1], width=0.01, label=f"n = {i + 2}")

# Add a vertical line indicating the accurate value of pi
plt.axvline(x=np.pi, color='r', linestyle='--', label='Actual π')

plt.title("Histograms for Different n Values (3D)")
plt.xlabel("Value")
plt.ylabel("Probability")

plt.tight_layout()
plt.savefig('pi_histograms_3D.png')
plt.clf()

# Report distribution average by weighting x values with p values
print("Results for 3D case")

average = np.sum(results[:, 0] * results[:, 1]) / np.sum(results[:, 1])
print(f"Average value of π from the distribution n=2: {average}")

average = np.sum(results[:, 2] * results[:, 3]) / np.sum(results[:, 3])
print(f"Average value of π from the distribution n=3: {average}")

average = np.sum(results[:, 4] * results[:, 5]) / np.sum(results[:, 5])
print(f"Average value of π from the distribution n=4: {average}")
