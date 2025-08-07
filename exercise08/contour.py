import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import os
import sys

# Get the absolute path to the build directory (relative to the script's location)
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, '..', 'build', 'exercise08')

# Append the build directory to sys.path
sys.path.append(build_dir)

# Import the self-made minimize module from the build directory
import minimize as minimize

# Create coordinate grids and evaluate the function in the grid
X, Y, Z = minimize.createFunctionGrid(-1, 1, -1, 1, 100)

# Create contour plot
plt.figure(figsize=(10, 8))
contours = plt.contour(X, Y, Z, levels=20, colors='black', alpha=0.6)
plt.contourf(X, Y, Z, levels=20, cmap='viridis', alpha=0.8)
plt.colorbar(label='f(x,y)')
plt.clabel(contours, inline=True, fontsize=8)

# Add optimization trajectory
try:
    xy_data = np.loadtxt(os.path.join(build_dir, 'xy.txt'))
    plt.plot(xy_data[:, 0], xy_data[:, 1], 'r-', linewidth=2, label='Optimization trajectory')
except Exception as e:
    print(f"Error loading trajectory data: {e}")

plt.xlabel('x')
plt.ylabel('y')
plt.title('Contour plot of f(x,y)')
plt.grid(True, alpha=0.3)
plt.savefig(os.path.join(current_dir, 'contour.pdf'))