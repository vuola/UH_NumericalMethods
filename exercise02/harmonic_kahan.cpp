#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * harmonic_kahan - sum of series with general term (1/k) with Kahan compensation
 *
 * @return Sum of (1/k) where k = { 1, ..., Nmax }, stops summing when float(1/k) == 0
 * or when N terms have been summed.
 * @throws None.
 *
 * Example:
 * @code
 * float sum = harmonic_kahan(N);
 * @endcode
 */
float harmonic_kahan(int N){

    float x,y,t;
    float sum=0.0;
    float e = 0.0;
    float previous_sum=0.0;
    int saturated = 0;

    for (int i=1; i<=N; ++i){
        previous_sum = sum;
        x = 1.0/i;
        y = x - e;
        t = sum + y;
        e = (t - sum) - y;
        sum = t;

        if (previous_sum == sum){
            saturated++;
        } 
    }

    cout << "times of saturation: " << saturated << endl;
    return sum;
}
