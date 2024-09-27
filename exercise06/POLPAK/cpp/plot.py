import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('test.txt')
x = data[:, 0]
y = data[:, 1]

data = np.loadtxt('bcurve.txt')
xb = data[:, 0]
yb = data[:, 1]

plt.plot(x, y, 'ro')
plt.plot(xb, yb, 'b-')
plt.show()
