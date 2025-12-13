import numpy as np
import matplotlib.pyplot as plt
import sys
import os

# Get the absolute path to the build directory (relative to the script's location)
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, '..', 'build', 'exercise11')

# Append the build directory to sys.path
sys.path.append(build_dir)

import shooting as shooting

# Create range of y-values
XY_10 = shooting.shootingRange(0.0, 1.0, 10, 1.0, 1.0)
XY_30 = shooting.shootingRange(0.0, 1.0, 30, 1.0, 1.0)
XY_100 = shooting.shootingRange(0.0, 1.0, 100, 1.0, 1.0)

# Plot to pdf file with reference function y = cos(x)+c*sin(x), c = (1-cos(1))/sin(1)
c = (1 - np.cos(1)) / np.sin(1)
plt.plot(XY_10[:,0], XY_10[:,1], 'r-', label='N=10')
plt.plot(XY_30[:,0], XY_30[:,1], 'g-', label='N=30')
plt.plot(XY_100[:,0], XY_100[:,1], 'b-', label='N=100')
plt.plot(XY_100[:,0], np.cos(XY_100[:,0])+c*np.sin(XY_100[:,0]), 'k--', label='y = cos(x)+c*sin(x)')
plt.legend()
plt.xlabel('x')
plt.ylabel('y(x)')
plt.title('Shooting Method Plot')
plt.grid(True)
plt.savefig(os.path.join(current_dir, 'shooting_plot.pdf'))