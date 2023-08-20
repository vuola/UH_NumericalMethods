#include <iostream>

using namespace std;

int main(int argc, char** argv){

    if (argc!=4) {
        fprintf(stderr,"Usage: %s x y z\n",argv[0]);
        return (1);
    }

    auto result = false;
    cout << argv[1] << endl;
    cout << argv[2] << endl;
    cout << argv[3] << endl;

    if(result){
        cout << "10 > 20\n";
    }else{
        cout << "10 < 20\n";
    }
}
