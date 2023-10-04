import math
import matplotlib.pyplot as plt
import numpy as np
import randomgenerator as rg

def exponential_approximation(x):
    n = round(x / math.log(2))
    y = x - n * math.log(2)
    result = math.exp(y) * 2**n
    return y

# Test with an example value of x

x = rg.portable_generator(13456,79676,1000) * 20 - 10
out = np.empty(1000)

for i in range(1000):
    out[i] = exponential_approximation(x[i])

plt.hist(out, bins=80, density=True, label='normal', alpha=0.7, edgecolor='yellow')
plt.show()