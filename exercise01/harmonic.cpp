#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief harmonic - sum of series with general term (1/k)
 *
 * @return Sum of (1/k) where k = { 1, ..., Nmax }. Reports to stdout the number events when consecutive
 * intermediate sums have been equal
 * @throws none
 *
 */
float harmonic(){

    /* Maximum number of terms */
    const int Nmax = 1000000000;

    float sum=0;
    float previous_sum=0;
    int saturated=0;

    for (int i=1; i<=Nmax; ++i){
        previous_sum = sum;
        sum += 1.0/i;

        if (previous_sum == sum){
            saturated++;
        } 
    }

    cout << "times of saturation: " << saturated << endl;
    return sum;
}

/**
 * @brief harmonic_bunch - sum of series with general term (1/k), terms summed in non-overlapping
 * batches
 *
 * @param N Number of terms in a batch
 * @return Sum of subsequent batches. A batch is sum of terms (1/k) where k = { n, ..., (n+N)-1) }
 * @throws none
 *
 */
float harmonic_bunch(int N){

    /* Maximum number of terms */
    int Nmax = 1000000000;

    float groupsum = 0;    
    int Cmax = Nmax / N;
    float sum;
    float previous_sum;

    for (int c=1; c<=Cmax; ++c){
        sum = 0; 
        previous_sum = 0;

        for (int i=(c-1)*N+1; i<=c*N; ++i) {
            previous_sum = sum;
            sum += 1.0/i;

            if (previous_sum == sum){
                cout << "float resolution limit at iteration " << i << endl;
                break;
            } 
        }
        groupsum += sum;
    }
    return groupsum;
}