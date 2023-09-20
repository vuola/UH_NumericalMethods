import numpy as np
import matplotlib.pyplot as plt
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