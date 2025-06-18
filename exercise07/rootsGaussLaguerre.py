import numpy as np
from scipy.special import roots_laguerre

for n in [2, 4, 8]:
    print(f"Number of nodes: {n}")
    x, w = roots_laguerre(n)
    print("Nodes (x):", x)
    print("Weights (w):", w)
    print()
