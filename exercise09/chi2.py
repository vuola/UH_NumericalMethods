import numpy as np
import matplotlib.pyplot as plt


def chi2(N, M):
    """
    Generate N uniformly distributed random numbers and calculate the chi-squared statistic.
    Calculate the chi-squared statistic for a given number of bins M.
    
    Parameters:
    N (int): Number of events
    M (int): Number of bins
    
    Returns:
    float: Chi-squared statistic
    """
    # Generate random data
    data = np.random.uniform(0, 1, N)
    # Create histogram
    hist, _ = np.histogram(data, bins=M, range=(0, 1))
    # Calculate expected values
    expected = N / M
    # Calculate chi-squared statistic
    chi2_stat = np.sum((hist - expected) ** 2 / expected)
    return chi2_stat


def test_chi2():
    """
    Test the chi2 with 100 random samples and 10 bins. Repeat the test 50 000 times and plot the histogram of the chi2 values.
    Report the mean of the chi2 values.
    """
    N = 100
    M = 10
    chi2_values = [chi2(N, M) for _ in range(50000)]
    plt.hist(chi2_values, bins=50, density=True, alpha=0.6, color='g')
    plt.xlabel('Chi-squared value')
    plt.ylabel('Density')
    plt.title('Histogram of Chi-squared values')
    plt.savefig('chi2_histogram.png')

    # Report mean 
    mean = np.mean(chi2_values)
    print(f"Mean Chi-squared value: {mean}")


if __name__ == "__main__":
    test_chi2()
    print("Chi-squared test completed and histogram saved.")
