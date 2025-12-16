
import matplotlib.pyplot as plt
import numpy as np
from sympy import *

print("""
###
Ex5 Prob3 (a) Lagrange method:
###
""")

x, x1, x2, x3 = symbols('x x1 x2 x3')
l_1 = (x-x2)*(x-x3)/((x1-x2)*(x1-x3))
l_2 = (x-x1)*(x-x3)/((x2-x1)*(x2-x3))
l_3 = (x-x1)*(x-x2)/((x3-x1)*(x3-x2))

f, f1, f2, f3 = symbols('f f1 f2 f3')
f = 1 / (1 + x**2)
f1 = f.subs(x, x1)
f2 = f.subs(x, x2)
f3 = f.subs(x, x3)

P = f1 * l_1 + f2 * l_2 + f3 * l_3
Pval = P.subs([(x1,0),(x2,1),(x3,3)])

print("Lagrange polynomial: ", expand(Pval))

print("""
###
Ex5 Prob3 (b) Newton method:
###
""")

x, x0, x1, f, y0, y1, y2, c, c1, c2 = symbols('x x0 x1 f y0, y1, y2, c c1 c2')

f = 1 / (1 + x**2)
y0 = f.subs(x,0)

print("Zero degree polynomial: ", y0)

P1 = y0 + c1 * (x - x0)
y1 = f.subs(x,1)
c = solve(Eq(P1,y1), c1)
c1i = c[0].subs([(x0, 0),(x, 1)])
P1 = P1.subs([(c1, c1i), (x0, 0)])

print("First degree polynomial: ", P1)
print("First degree coefficient: ", c1i)

P2 = P1 + c2 * (x - x0) * (x - x1)
y2 = f.subs(x,3)
c = solve(Eq(P2,y2), c2)
c2i = c[0].subs([(x0, 0),(x1, 1),(x, 3)])
P2 = P2.subs([(c2, c2i), (x0, 0), (x1, 1)])

print("Second degree polynomial: ", P2)
print("Second degree coefficient: ", c2i)

print("Newton polynomial: ", expand(P2))

# Plot the function and polynomial


x = np.arange(-0.5, 3.5, 0.05)

fx = 1 / (1 + x**2)
pol = x**2/10 - 3*x/5 + 1

# red dashes, blue squares and green triangles
plt.title("Function y = 1/(1+x^2) RED, 2nd deg Polynome fit GRN")
plt.plot(x, fx, 'r-', x, pol, 'g--')
plt.savefig("exercise5_3.png")