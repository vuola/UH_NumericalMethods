from numpy.polynomial import Polynomial
import numpy as np
import matplotlib.pyplot as plt

def spline(i,k,t_i):
    """
    Return the i-th spline of degree k with left endpoint t_i in range [t_i, t_i+1].
    Simplified version with t_i=i.
    i: int, the index of the spline
    k: int, the degree of the spline
    t_i: int, the left endpoint of the spline
    """
    Z = Polynomial([0])
    if k == 0:
        if i <= t_i and t_i < i+1:         
            return Polynomial([1], symbol='t')
        else: 
            return Polynomial([0], symbol='t')
    else:    
        A = Polynomial([-i, 1], symbol='t')
        B = Polynomial([k+i+1, -1], symbol='t')

        Nikm1 = spline(i,k-1,t_i)
        Nip1km1 = spline(i+1,k-1,t_i)

        if Nikm1 == Z:
            return (1/k) * B * Nip1km1
        elif Nip1km1 == Z:
            return (1/k) * A * Nikm1
        else:
            return (1/k) * (A * Nikm1 + B * Nip1km1)
            
 
def test_spline():
    # Test the function with some examples

    # Zero polynomial
    Z = Polynomial([0])

    # Colormap
    c = [plt.cm.tab10(i) for i in range(7)]

    # Up to three degrees
    print("First degree splines")
    print("********************")
    for t in range(0,8):
        x = np.linspace(t, t+1, 20, endpoint=True)
        print("Segment [", t, ",", t+1, ")")
        for i in range(t-1,t+1):
            S = spline(i,1,t)
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
            S = spline(i,2,t)
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
            S = spline(i,3,t)
            if i >= 0 and S != Z and i < (8-3):
                print(f"N({i},3):", S)
                F = S(x)
                if (t == i): plt.plot(x, F, color=c[i], label=f"N({i},3)") 
                else: plt.plot(x, F, color=c[i])
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.title("Third degree splines")
    plt.savefig("spline3.png")
    


test_spline()