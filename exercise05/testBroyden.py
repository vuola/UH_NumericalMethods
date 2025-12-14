import numpy as np

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

add_solver_to_path('exercise05')

import broyden as br

def F(x):
   out = np.array([np.exp(-(x[0]**2+x[1]**2))-(1/8), np.sin(x[0])-np.cos(x[1])])
   return out[::-1]
import scipy.optimize
x = scipy.optimize.broyden1(F, [1,1], f_tol=1e-14)

print("Scipy solution:")
print("Roots: ", x)
print("F: ", F(x), "\n")

x = br.broyden(np.array([1,1]))
fx = br.f(x)

print("Own solution:")
print("Roots: ", x)
print("F: ", fx, "\n")




