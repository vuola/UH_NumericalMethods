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

add_solver_to_path('exercise03')

import jacobi as j
 
N = np.array([8, 9, 10, 11, 12], np.int32) 
dq = np.array([0.008, 0.009, 0.01, 0.011, 0.012])

D = j.jacobiRange(N, dq, 100)

np.set_printoptions(suppress='true')
np.set_printoptions(precision=3)

print("Data:")
print("   N\t","  dq\t","mean\t","std\t")
print(np.transpose(D))

