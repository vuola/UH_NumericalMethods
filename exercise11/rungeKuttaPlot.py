import numpy as np
import matplotlib.pyplot as plt
import sys
import os

# Get the absolute path to the build directory (relative to the script's location)
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, '..', 'build', 'exercise11')

# Append the build directory to sys.path
sys.path.append(build_dir)

import rungeKutta as rungeKutta

# Create range of y-values
XY_30 = rungeKutta.rungeKuttaRange(0.0, 10.0, 30, 1.0, 0.0)
XY_100 = rungeKutta.rungeKuttaRange(0.0, 10.0, 100, 1.0, 0.0)
XY_300 = rungeKutta.rungeKuttaRange(0.0, 10.0, 300, 1.0, 0.0)

# Plot to pdf file with reference function y = cos(x)
plt.plot(XY_30[:,0], XY_30[:,1], 'r-', label='N=30')
plt.plot(XY_100[:,0], XY_100[:,1], 'g-', label='N=100')
plt.plot(XY_300[:,0], XY_300[:,1], 'b-', label='N=300')
plt.plot(XY_300[:,0], np.cos(XY_300[:,0]), 'k--', label='y = cos(x)')
plt.legend()
plt.xlabel('x')
plt.ylabel('y(x)')
plt.title('Runge-Kutta Plot')
plt.grid(True)
plt.savefig(os.path.join(current_dir, 'runge_kutta_plot.pdf'))