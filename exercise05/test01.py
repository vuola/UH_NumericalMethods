import numpy as np

def F(x):
   out = np.array([np.exp(-(x[0]**2+x[1]**2))-(1/8), np.sin(x[0])-np.cos(x[1])])
   return out[::-1]
import scipy.optimize
x = scipy.optimize.broyden1(F, [1,1], f_tol=1e-14)

print("Roots: ", x)
print("F: ", F(x))

