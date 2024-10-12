import numpy as np
import matplotlib.pyplot as plt

import sys
import os

# Get the absolute path to the build directory (relative to the script's location)
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, '..', 'build', 'exercise03')

# Append the build directory to sys.path
sys.path.append(build_dir)

import jacobi as j


 
Q = np.array([[0.61611086,   0.03563731,   0.28538886,   0.37600851,   0.32336015,   0.97817445], 
  [0.03563731,   0.08815959,   0.71970248,   0.74768132,   0.29026943,   0.31981957], 
  [0.28538886,   0.71970248,   0.50220811,   0.44811806,   0.00099506,   0.94624835], 
  [0.37600851,   0.74768132,   0.44811806,   0.17185755,   0.19949169,   0.63531208], 
  [0.32336015,   0.29026943,   0.00099506,   0.19949169,   0.2208458,    0.53851491],
  [0.97817445,   0.31981957,   0.94624835,   0.63531208,   0.53851491,   0.72695738]]) 

N = 6

coeff = np.sort(j.jacobi(Q, N))
print("Markus: ", coeff)


coeff2 = np.sort(np.linalg.eig(Q)[0])
print("Python: ", coeff2)

print("Diff:   ", coeff - coeff2)

