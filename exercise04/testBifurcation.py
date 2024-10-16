import numpy as np
import matplotlib.pyplot as plt

import sys
import os

# Get the absolute path to the build directory (relative to the script's location)
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, '..', 'build', 'exercise04')

# Append the build directory to sys.path
sys.path.append(build_dir)

import bifurcation as b
 
mu = np.array([2.5, 3.0, 3.2, 3.5], np.int32) 

D = b.frange(mu, 0.3, 1.0, 10)
print(D)

x_range = D[0,:]
y_25 = D[1,:]
y_30 = D[2,:]
y_32 = D[3,:]
y_35 = D[4,:]

# Create the plot
plt.figure(figsize=(10, 6))
plt.plot(x_range, y_25, label='mu=2.5')
plt.plot(x_range, y_30, label='mu=3.0')
plt.plot(x_range, y_32, label='mu=3.2')
plt.plot(x_range, y_35, label='mu=3.5')


# Add labels and title
plt.xlabel('x')
plt.ylabel('f(x)')
plt.title('Bifurcating function')
plt.legend()

# Display the plot
plt.grid(True)
plt.show()

###
### Fractals
###

D2 = b.bifurcation(0.5, 2.5, 3.0, 10)

mu_range = D2[0,:]
y_f1 = D2[1,:]
y_f2 = D2[2,:]

# Create the plot
plt.figure(figsize=(10, 6))
# plt.plot(mu_range, y_f1, label='fractal 1')
plt.plot(mu_range, y_f2, label='fractal 2')


# Add labels and title
plt.xlabel('mu')
plt.ylabel('x(N)')
plt.title('Bifurcating series')
plt.legend()

# Display the plot
plt.grid(True)
plt.show()
