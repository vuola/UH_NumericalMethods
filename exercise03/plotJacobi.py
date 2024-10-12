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
 
N = np.array([8, 9, 10, 11, 12], np.int32) 
dq = np.array([0.008, 0.009, 0.01, 0.011, 0.012])

D = j.jacobiRange(N, dq, 100)

np.set_printoptions(suppress='true')
np.set_printoptions(precision=3)

print("Data:")
print("   N\t","  dq\t","mean\t","std\t")
print(np.transpose(D))

