import numpy as np
import matplotlib.pyplot as plt
import myroots as my
 
a = np.array([2.0, -3.0, 1.0], np.int32) 
r = my.myroots(2,a)
print(r)
ze = my.evalP(a,r)
print(ze)