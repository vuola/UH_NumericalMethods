import numpy as np
import matplotlib.pyplot as plt
import sys
import os

# Get the absolute path to the build directory (relative to the script's location)
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, '..', 'build', 'exercise11')

# Append the build directory to sys.path
sys.path.append(build_dir)

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
plt.savefig(os.path.join(current_dir, 'finite_difference_stencil_plot.pdf'))
