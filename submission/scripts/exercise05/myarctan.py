import math
import matplotlib.pyplot as plt
import numpy as np
import randomgenerator as rg

def myarctan(x):
    # Reduce x to the range [0, Inf]
    sign = 1
    if x < 0:
        x = -x
        sign = -1
    
    # Reduce x to the range [0, 1]
    if x > 1:
        x = 1 / x
        return sign * ((math.pi / 2) - math.atan(x))
    else:
        return sign * math.atan(x)



# Test error distribution with example values of x

x = rg.portable_generator(13456,79676,1000) * 20 - 10
out = np.empty(1000)

for i in range(1000):
    out[i] = myarctan(x[i]) - math.atan(x[i])
    if out[i] < -1000:
        print("x[i]: ", x[i])

plt.hist(out, bins=80, density=True, label='normal', alpha=0.7, edgecolor='yellow')
plt.title("Error distribution of { myarctan(x) - math.atan(x) }")
plt.savefig("myarctan_error_distribution.png")