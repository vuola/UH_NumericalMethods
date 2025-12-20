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

add_solver_to_path('exercise11')

import fds as fds

# Create theoretical reference values for 5 first energies
n = np.arange(1, 6)
E_ref = n**2 * np.pi**2 / 8
print(f'Theoretical reference energies: {[f"{e:.4f}" for e in E_ref]}')

# Create energies and wave functions
N=20
alldata = fds.finiteDifference(N, 2/N)
smallfive = alldata[-5:, 0][::-1]
error = np.sqrt(np.mean((smallfive - E_ref) ** 2))
print(f'N={N}, smallest five energies: {[f"{e:.4f}" for e in smallfive]}, error: {error:.4f}')

# Repeat with doubling N until error < 0.03
while error > 0.03:
    N *= 2
    alldata = fds.finiteDifference(N, 2/N)
    smallfive = alldata[-5:, 0][::-1]
    error = np.sqrt(np.mean((smallfive - E_ref) ** 2))
    print(f'N={N}, smallest five energies: {[f"{e:.4f}" for e in smallfive]}, error: {error:.4f}')

for i in range(N-4, N+1):
    plt.plot(np.linspace(-1.0, 1.0, N), alldata[:, i], label=f'Wavefunction {i}')
plt.legend()
plt.xlabel('x')
plt.ylabel('y(x)')
plt.title('Finite Difference Stencil Plot')
plt.grid(True)
plt.savefig('finite_difference_stencil_plot.pdf')
