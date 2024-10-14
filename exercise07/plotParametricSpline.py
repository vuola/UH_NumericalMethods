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
        if t >= ti[i] and t < ti[i+1]:         
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
            


def test_spline():
    # Test the function with some examples

    # Zero polynomial
    Z = Polynomial([0], symbol='t')

    # Colormap
    c = [plt.cm.tab10(i) for i in range(7)]

    # Knot values
    ti = np.linspace(0,11,12)

    # Up to three degrees
    print("First degree splines")
    print("********************")
    for t in range(0,8):
        x = np.linspace(t, t+1, 20, endpoint=True)
        print("Segment [", t, ",", t+1, ")")
        for i in range(t-1,t+1):
            S = spline(i,1,t,ti)
            if i >= 0 and S != Z and i < (8-1):
                print(f"N({i},1):", S)
                F = S(x)
                if (t == i): plt.plot(x, F, color=c[i], label=f"N({i},1)") 
                else: plt.plot(x, F, color=c[i])
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.title("First degree splines")
    plt.tight_layout()
    plt.savefig("spline1.png")
    plt.clf()
    print("Second degree splines")
    print("********************")
    for t in range(0,8):
        x = np.linspace(t, t+1, 20, endpoint=True)
        print("Segment [", t, ",", t+1, ")")
        for i in range(t-2,t+1):
            S = spline(i,2,t,ti)
            if i >= 0 and S != Z and i < (8-2):
                print(f"N({i},2):", S)
                F = S(x)
                if (t == i): plt.plot(x, F, color=c[i], label=f"N({i},2)") 
                else: plt.plot(x, F, color=c[i])
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.title("Second degree splines")
    plt.savefig("spline2.png")
    plt.clf()
    print("Third degree splines")
    print("********************")
    for t in range(0,8):
        x = np.linspace(t, t+1, 20, endpoint=True)
        print("Segment [", t, ",", t+1, ")")
        for i in range(t-3,t+1):
            S = spline(i,3,t,ti)
            if i >= 0 and S != Z and i < (8-3):
                print(f"N({i},3):", S)
                F = S(x)
                if (t == i): plt.plot(x, F, color=c[i], label=f"N({i},3)") 
                else: plt.plot(x, F, color=c[i])
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.title("Third degree splines")
    plt.savefig("spline3.png")
    


def test_parametric_spline():
    # Test the function with a parametric spline in xy plane

    # Zero polynomial
    Z = Polynomial([0], symbol='t')

    # Colormap
    c = [plt.cm.tab10(i) for i in range(10)]

    # Number of knots
    n = 14
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
    #    print(t)
        X[t] = x(t/100,ti,xi,m)
        Y[t] = y(t/100,ti,yi,m)

    #print("X:", X)
    #print("Y:", Y)

    plt.plot(X,Y, color=c[0])
    plt.plot(xi,yi, 'ro')
    plt.tight_layout()
    plt.savefig("parametricSpline.png")
    

test_parametric_spline()
#test_spline()