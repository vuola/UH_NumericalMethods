import numpy as np
import matplotlib.pyplot as plt
import funks as fu

# Generate X values in a defined range and resolution
# Generate four sets of Y values based on funksRange algorithm
# XY = fu.funksRange(-0.0000001, 0.0000001, 201)
XY = fu.funksRange(-3, 3, 201)

x_range = XY[0,:]
f_1 = XY[1,:]  # first function
T_1 = XY[2,:]  # first Taylor function
f_2 = XY[3,:]  # second function
T_2 = XY[4,:]  # second Taylor function
e_1_1 = XY[5,:]
e_1_2 = XY[6,:]
e_1_3 = XY[7,:]
e_2_1 = XY[8,:]
e_2_2 = XY[9,:]
e_2_3 = XY[10,:]

# Create the plot
plt.figure(figsize=(10, 6))
#plt.plot(x_range, f_1, label='Function 1')
#plt.plot(x_range, T_1, label='Function 1 Taylor')
plt.plot(x_range, f_2, label='Function 2')
plt.plot(x_range, T_2, label='Function 2 Taylor')
#plt.plot(x_range, e_1_1, label='error Taylor 1 n=1')
#plt.plot(x_range, e_1_2, label='error Taylor 1 n=2')
#plt.plot(x_range, e_1_3, label='error Taylor 1 n=3')
plt.plot(x_range, e_2_1, label='error Taylor 2 n=1')
plt.plot(x_range, e_2_2, label='error Taylor 2 n=2')
plt.plot(x_range, e_2_3, label='error Taylor 2 n=3')


# Add labels and title
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Trigonometric and exponent functions with their Taylor series n=3')
plt.legend()

# Display the plot
plt.grid(True)
plt.show()
