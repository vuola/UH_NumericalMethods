import numpy as np
import matplotlib.pyplot as plt
import jacobi as j


Q = np.random.rand(3,3)
print(Q)

N = 3

coeff = j.jacobi(Q, N)

print(coeff)

