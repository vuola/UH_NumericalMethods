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

add_solver_to_path('exercise09')

# Use the self-created library
import moment as moment

results = moment.verifyRNG()

# Plot two timeseries, first with random averages on the same graph 
# with two different N values, and 
# second with random numbers squared and averaged, with two different N values.

import matplotlib.pyplot as plt

# Extract the data for plotting
random_averages_1000 = results[:, 0]
squared_averages_1000 = results[:, 1]
random_averages_1000000 = results[:, 2]
squared_averages_1000000 = results[:, 3]

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
