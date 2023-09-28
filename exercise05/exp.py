import math

def exponential_approximation(x):
    n = round(x / math.log(2))
    y = x - n * math.log(2)
    result = math.exp(y) * 2**n
    return result

# Test with an example value of x
x = 2.0
result = exponential_approximation(x)
print(f"e^{x} is approximately {result}")
