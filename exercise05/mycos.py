import math
import matplotlib.pyplot as plt
import numpy as np
import randomgenerator as rg

def mycos(x):
    # Reduce x to the range [0, 2*pi]
    x = x % (2 * math.pi)
    
    # Reduce x to the range [0, pi]
    if x > math.pi:
        x = 2 * math.pi - x
        return math.cos(x)
    else:
        # reduce x to the range [0. pi/2] 
        if x > (math.pi / 2):
            x = math.pi - x
            return -math.cos(x)

    # reduce x to the range [0, pi/4]
    if x > (math.pi / 4):
        x = (math.pi / 2) - x
        return math.sqrt(1 - math.cos(x)**2)
    else:
        return math.cos(x)



# Test error distribution with example values of x

x = rg.portable_generator(13456,79676,1000) * 20 - 10
out = np.empty(1000)

for i in range(1000):
    out[i] = mycos(x[i]) - math.cos(x[i])
    if out[i] < -1000:
        print("x[i]: ", x[i])

plt.hist(out, bins=80, density=True, label='normal', alpha=0.7, edgecolor='yellow')
plt.title("Error distribution of { mycos(x) - math.cos(x) }")
plt.savefig("mycos_error_distribution.png")