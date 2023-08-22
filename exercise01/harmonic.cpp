#include <iostream>
#include <stdlib.h>

using namespace std;

float harmonic(int N){
    float sum=0;
    for (int i=0; i<N; i++){
        sum += 1/(i+1);
    }
    return sum; 
}

int main(int argc, char** argv){

    if (argc!=2) {
        fprintf(stderr,"Usage: %s k\n",argv[0]);
        return (1);
    }

    int i;
    sscanf(argv[1], "%d", &i);
    cout << harmonic(i) << endl;
    return 0;
}
