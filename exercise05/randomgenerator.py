import numpy as np


def portable_generator(s1,s2,N):
    """
    Random number generator producing an even distribution
    @param s1: random seed 1 must be integer in range [1, 2147483562]
    @param s2: random seed 2 must be integer in range [1, 2147483398]
    @param N: number of samples to be generated
    @return: an N-array of random float numbers with values between [0.0, ..., 1.0]

    The algorithm is described in article:
    L'ecuyer 1988 Efficent and Portable Combined Random Number Generators, Communications of the ACM V31, N6
    """

    # Parameters for generator 1
    m1 = 2147483563
    a1 = 40014
    q1 = m1 // a1
    r1 = m1 % a1

    # Parameters for generator 2
    m2 = 2147483399
    a2 = 40692
    q2 = m2 // a2
    r2 = m2 % a2

    out = np.empty(N)

    for i in range(N):
        k = s1 // q1
        s1 = a1 * (s1 - k * q1) - k * r1
        if (s1 < 0):
            s1 = s1 + m1

        k = s2 // q2
        s2 = a2 * (s2 - k * q2) - k * r2
        if (s2 < 0):
            s2 = s2 + m2

        z = s1 - s2
        if (z < 1):
            z = z + m1 - 1
        u = z / m1

#        print(i, u)
        out[i] = u

    return out