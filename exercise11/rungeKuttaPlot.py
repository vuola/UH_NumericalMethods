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