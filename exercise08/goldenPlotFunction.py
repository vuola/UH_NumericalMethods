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

add_solver_to_path('exercise08')

import golden as golden

# Create range of y-values
XY = golden.goldenRange(0.0, 4.0, 100)

# Plot to pdf file
plt.plot(XY[0], XY[1], 'r-')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.title('Golden Range Plot')
plt.grid(True)
plt.savefig('golden_range_plot.pdf')


