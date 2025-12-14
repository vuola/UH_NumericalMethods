import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
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

add_solver_to_path('exercise08')

# Import the self-made minimize module from the build directory
import minimize as minimize

# Create coordinate grids and evaluate the function in the grid
X, Y, Z = minimize.createFunctionGrid(-11, 21, -11, 11, 1000)

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
plt.title('BFGS')
plt.grid(True, alpha=0.3)
plt.savefig('BFGS_A.pdf')