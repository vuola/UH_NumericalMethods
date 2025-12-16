import math
import matplotlib.pyplot as plt
import numpy as np
import randomgenerator as rg

def myln(x):
    # Check if range is valid
    if x > 0:
        # Reduce x to the range [1, Inf]
        if x < 1:
            x = 1/x
            return -myln(x)
        else:
        # Reduce x recursively to the range [1,2]
            if x > 2:
                x = x / 2
                return math.log(2) + myln(x)
            else:
                return math.log(x)
    else:
        # invalid input
        return float('nan')



# Test error distribution with example values of x

x = rg.portable_generator(13456,79676,1000) * 20
out = np.empty(1000)

for i in range(1000):
    out[i] = myln(x[i]) - math.log(x[i])
    if out[i] < -1000:
        print("x[i]: ", x[i])

plt.hist(out, bins=80, density=True, label='normal', alpha=0.7, edgecolor='yellow')
plt.title("Error distribution of { myln(x) - math.log(x) }")
plt.savefig("myln_error_distribution.png")