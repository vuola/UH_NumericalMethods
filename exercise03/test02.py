import numpy as np
import matplotlib.pyplot as plt
import jacobi as j
 
N = np.array([8, 9, 10, 11, 12], np.int32) 
dq = np.array([0.008, 0.009, 0.01, 0.011, 0.012])

D = j.jacobiRange(N, dq, 100)

np.set_printoptions(suppress='true')
np.set_printoptions(precision=3)

print("Data: ", np.transpose(D))

