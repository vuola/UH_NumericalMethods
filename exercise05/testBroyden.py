import numpy as np

import sys
import os

# Get the absolute path to the build directory (relative to the script's location)
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, '..', 'build', 'exercise05')

# Append the build directory to sys.path
sys.path.append(build_dir)

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




