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
        os.path.join(current_dir, '..', 'build', exercise_name),

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

add_solver_to_path('exercise06')

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

