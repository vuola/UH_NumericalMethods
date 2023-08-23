import numpy as np
import matplotlib.pyplot as plt
import funks as fu

# Generate X values in a defined range and resolution
# Generate two sets of Y values based on funks algorithm
XY = fu.funksRange(-4.0, 4.0, 100)

x_range = XY[0,:]
signal_1 = XY[1,:]  # first function
signal_2 = XY[2,:]  # second function

# Create the plot
plt.figure(figsize=(10, 6))
plt.plot(x_range, signal_1, label='Function 1')
plt.plot(x_range, signal_2, label='Function 2')

# Add labels and title
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Trigonometric and exponent function')
plt.legend()

# Display the plot
plt.grid(True)
plt.show()
