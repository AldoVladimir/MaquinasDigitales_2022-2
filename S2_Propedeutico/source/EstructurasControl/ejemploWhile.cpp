#include <iostream>
using namespace std;

int main(){

    int arr[10];
    int d = 0, pos = 0;
    float res = 0;

    while(d >= 0 && pos < 10){
        cout << "Ingrese el dato [" << pos+1 << "]: ";
        cin >> d;
        if(d >= 0){
            arr[pos] = d;
            pos++;          // pos = pos + 1;
            res+=d;         // res = res + d;
        }
    }

    cout << "El promedio es: " << res/pos << endl;

    return 0;
}