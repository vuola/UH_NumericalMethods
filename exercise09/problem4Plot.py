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
import problem4 as problem4

results = problem4.verifyRNG()

# Plot two timeseries, first with random averages on the same graph 
# with two different N values, and 
# second with random numbers squared and averaged, with two different N values.

import matplotlib.pyplot as plt

# Extract the data for plotting
random_averages_1000 = results[0, :]
random_averages_1000000 = results[2, :]
squared_averages_1000 = results[1, :]
squared_averages_1000000 = results[3, :]

# Create the figure and axis objects
fig, axs = plt.subplots(2, 1, figsize=(10, 8))

# Plot the first timeseries
axs[0].plot(random_averages_1000, label='Random Averages (N=1000)')
axs[0].plot(random_averages_1000000, label='Random Averages (N=1000000)')
axs[0].set_title('Random Averages')
axs[0].set_xlabel('Experiment')
axs[0].set_ylabel('Average Value')
axs[0].legend()

# Plot the second timeseries
axs[1].plot(squared_averages_1000, label='Squared Averages (N=1000)')
axs[1].plot(squared_averages_1000000, label='Squared Averages (N=1000000)')
axs[1].set_title('Squared Averages')
axs[1].set_xlabel('Experiment')
axs[1].set_ylabel('Average Value')
axs[1].legend()

# Show the plots
plt.tight_layout()
plt.savefig('random_vs_squared_averages.png')
