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

import gaussrng as g

# Call the verifyLorentzDistribution function
result = g.verifyLorentzDistribution(100, 10**6, -10.0, 10.0)

# Extract x and p values (numerical distribution) from the result
x_values = result[0, :]
p_values = result[1, :]
# Extract pref (theoretical distribution) from the result
pref = result[2, :]
    
# Plotting
plt.figure(figsize=(10, 6))
plt.bar(x_values, p_values, width=(x_values[1] - x_values[0]), alpha=0.7, label='Numerical')
plt.plot(x_values, pref, color='red', linewidth=2, label='Theoretical')
plt.title('Distribution of Lorentz Function')
plt.xlabel('x')
plt.ylabel('Probability Density')
plt.grid()
plt.legend()
plt.savefig('lorentzByQuotient.png')
