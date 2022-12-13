#include <iostream>

using namespace std;

int main(){
    int a=5;
    for(int i=0; i<10 && a<10; i++){
        a++;
        cout << i << "\t" << a << endl;
    }
}