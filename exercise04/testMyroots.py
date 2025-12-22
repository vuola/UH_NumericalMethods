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
        os.path.join(current_dir, '..', 'build', 'runtime'),

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

add_solver_to_path('exercise04')

import myroots as my
import random

N = 10
genroots = np.empty(N)
for i in range (0, N):
    genroots[i] = np.random.uniform(-5, 5)
# a = np.array([2.0, -3.0, 1.0], np.int32)
print("Generated random roots:\n",genroots,"\n") 

a = np.polynomial.polynomial.polyfromroots(genroots)
print("Polynomial P(x) coefficients from generated roots: \n", a, "\n")

r = my.myroots(N,a)
print("Calculated Roots from polynomial P(x): \n",r,"\n")

ze = my.evalP(a,r)
print("P(x) evaluated at roots:\n", ze, "\n")

err = np.linalg.norm(ze)
print("Norm of error:\n", err, "\n")           