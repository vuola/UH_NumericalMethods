import numpy as np
import matplotlib.pyplot as plt
import sys
import os

# Get the absolute path to the build directory (relative to the script's location)
current_dir = os.path.dirname(os.path.abspath(__file__))
build_dir = os.path.join(current_dir, '..', 'build', 'exercise08')

# Append the build directory to sys.path
sys.path.append(build_dir)

import golden as golden

# Create range of y-values
Y = golden.goldenRange(0.0, 10.0, 100)

# Plot to pdf file
plt.plot(Y, 'r-')
plt.xlabel('Index')
plt.ylabel('Value')
plt.title('Golden Range Plot')
plt.grid(True)
plt.savefig(os.path.join(current_dir, 'golden_range_plot.pdf'))


