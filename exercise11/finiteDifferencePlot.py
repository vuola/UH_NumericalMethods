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

# Create energies and wave functions
N=1280
alldata = fds.finiteDifference(N, 2/N)

print("Last 5 energies:\n", alldata[-5:, 0])

for i in range(N-4, N+1):
    plt.plot(np.linspace(-1.0, 1.0, N), alldata[:, i], label=f'Wavefunction {i}')
plt.legend()
plt.xlabel('x')
plt.ylabel('y(x)')
plt.title('Finite Difference Stencil Plot')
plt.grid(True)
plt.savefig(os.path.join(current_dir, 'finite_difference_stencil_plot.pdf'))
