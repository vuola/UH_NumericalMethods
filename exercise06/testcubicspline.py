import numpy as np
import matplotlib.pyplot as plt

import sys
import os

# Get the absolute path to the build directory (relative to the script's location)
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, '..', 'build', 'exercise06')

# Append the build directory to sys.path
sys.path.append(build_dir)

import cubicspline as cs

boundary = np.array([0.0, 1.0, 10.0])


#
# Plot with n=10
#
D = cs.cubicspline(10, boundary)

# Collect fixed points F from every fourth row of D starting from first row
F = D[0::4, :]

x = D[:,0]
y1 = D[:,1]
y2 = D[:,2]
y3 = D[:,3]

plt.figure(figsize=(10, 6))
plt.plot(x, y1, label='y(0)=0')
plt.plot(x, y2, label='y(0)=1')
plt.plot(x, y3, label='y(0)=10')
plt.plot(F[:,0], F[:,1], 'ro')

plt.xlabel('x')
plt.ylabel('y')
plt.title('Cubic spline n=10')

plt.legend()
plt.grid(True)

plt.savefig("cubicspline_10.png")
# reset plot
plt.clf()

#
# Plot with n=5
#
D = cs.cubicspline(5, boundary)

# Collect fixed points F from every fourth row of D starting from first row
F = D[0::4, :]
x = D[:,0]
y1 = D[:,1]
y2 = D[:,2]
y3 = D[:,3]

plt.figure(figsize=(10, 6))
plt.plot(x, y1, label='y(0)=0')
plt.plot(x, y2, label='y(0)=1')
plt.plot(x, y3, label='y(0)=10')
plt.plot(F[:,0], F[:,1], 'ro')

plt.xlabel('x')
plt.ylabel('y')
plt.title('Cubic spline n=5')

plt.legend()
plt.grid(True)

plt.savefig("cubicspline_5.png")
# reset plot
plt.clf()

#
# Plot with n=20
#
D = cs.cubicspline(20, boundary)

# Collect fixed points F from every fourth row of D starting from first row
F = D[0::4, :]
x = D[:,0]
y1 = D[:,1]
y2 = D[:,2]
y3 = D[:,3]

plt.figure(figsize=(10, 6))
plt.plot(x, y1, label='y(0)=0')
plt.plot(x, y2, label='y(0)=1')
plt.plot(x, y3, label='y(0)=10')
plt.plot(F[:,0], F[:,1], 'ro')

plt.xlabel('x')
plt.ylabel('y')
plt.title('Cubic spline n=20')

plt.legend()
plt.grid(True)

plt.savefig("cubicspline_20.png")

