from numpy.polynomial import Polynomial
import numpy as np
import matplotlib.pyplot as plt

def spline(i,k,t,ti):
    """
    Return the i-th spline of degree k within range [ ti[i] , ti[i+1] ).
    i: int, the index of the left endpoint of the spline
    k: int, the degree of the spline
    t: double, the evaluation point of the spline
    ti: double, the knot values
    """
    Z = Polynomial([0], symbol='t')
    if k == 0:
        if ti[i] <= t < ti[i+1]:         
            return Polynomial([1], symbol='t')
        else: 
            return Polynomial([0], symbol='t')
    elif i+k+1 >= len(ti):
        return Z
    else:    
        A = Polynomial([-ti[i], 1], symbol='t') / (ti[i+k]-ti[i])
        B = Polynomial([ti[i+k+1], -1], symbol='t') / (ti[i+k+1]-ti[i+1])

        Nikm1 = spline(i,k-1,t,ti)
        Nip1km1 = spline(i+1,k-1,t,ti)

        if Nikm1 == Z:
            return B * Nip1km1
        elif Nip1km1 == Z:
            return A * Nikm1
        else:
            return (A * Nikm1 + B * Nip1km1)



def test_parametric_spline():
    # Test the function with a parametric spline in xy plane

    # Zero polynomial
    Z = Polynomial([0], symbol='t')

    # Colormap
    c = [plt.cm.tab10(i) for i in range(10)]

    # Number of knots
    n = 25 
    # Spline degree
    k = 3
    # Number of control points
    m = n - k - 1

    # Knot values between 0 and 1
    ti = np.linspace(0,1,n)

    # Control points
    theta = np.linspace(0, 2 * np.pi, m, endpoint=False)
    radius = 5  # Radius of the circle
    xi = radius * np.cos(theta)
    yi = radius * np.sin(theta)
    # Add some random noise to the control points
    xi += np.random.normal(0, 0.5, m)
    yi += np.random.normal(0, 0.5, m)

    # print("xi:",xi)
    # print("yi:",yi)

    # Parametric spline
    def x(t,ti,xi,m):
        S = Z
        for i in range(m):
            S += xi[i] * spline(i,k,t,ti)
        return S(t)


    def y(t,ti,yi,m):
        S = Z
        for i in range(m):
            S += yi[i] * spline(i,k,t,ti)
        return S(t)


    # Plot the parametric spline
    
    X = np.zeros(100)
    Y = np.zeros(100)

    for t in range(100):
        # tt goes from 10% to 90% to avoid the zero endpoints
        tt = 0.1 + 0.8 * t / 100
        X[t] = x(tt,ti,xi,m)
        Y[t] = y(tt,ti,yi,m)


    plt.plot(X,Y, color=c[0])
    plt.plot(xi,yi, 'ro')
    plt.tight_layout()
    plt.savefig("parametricSpline.png")
    

test_parametric_spline()
#test_spline()