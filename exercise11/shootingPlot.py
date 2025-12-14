import numpy as np
import matplotlib.pyplot as plt
import sys
import os

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

add_solver_to_path('exercise11')

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